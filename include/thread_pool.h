#ifndef THREAD_POOL_AJDLKAS_H
#define THREAD_POOL_AJDLKAS_H
#include <thread>
#include <vector>
#include <queue>
#include <functional>
#include <condition_variable>
#include <iostream>

class ThreadPool
{

  public: 
    ThreadPool(int pool_count = std::thread::hardware_concurrency()):m_pool_count{pool_count}
    {
      std::cerr << "starting " << pool_count << " threads\n";
      for (int i=0; i<pool_count; ++i)
      {
        m_pool.push_back({std::thread(&ThreadPool::infinite_loop, this)});
      }
    }

    void infinite_loop();
    void add_job(std::function<void()> job);
    void shutdown();

    ~ThreadPool(){if (!m_is_shut) shutdown();}

  protected:
    int m_pool_count;

    bool m_is_shut{false};
    bool m_shutdown_flag{false};
    std::queue<std::function<void()>> m_jobs;
    std::vector<std::thread> m_pool;
    std::mutex m_mutex_queue;
    std::condition_variable cv;


};

#endif