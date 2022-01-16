#include "thread_pool.h"

#include <thread>
#include <mutex>
#include <queue>
#include <condition_variable>
#include <functional>

void ThreadPool::infinite_loop()
{
  while (true)
  { 
    std::function<void()> job;
    {
      std::unique_lock<std::mutex> lock(m_mutex_queue);
      cv.wait(lock, [this](){return !m_jobs.empty() || m_shutdown_flag;});
      if (m_jobs.empty()) break;
      job = m_jobs.front();
      m_jobs.pop();
    }
    job();
  }
}

void ThreadPool::add_job(std::function<void()> new_job)
{
  {
    std::unique_lock<std::mutex> lock(m_mutex_queue);
    m_jobs.push(new_job);
  }
  cv.notify_one();
}

bool ThreadPool::any_jobs()
{
  return !m_jobs.empty();

}

void ThreadPool::shutdown()
{
  m_shutdown_flag = true;
  cv.notify_all(); 
  for (auto &th: m_pool){
    th.join();
  };
  m_pool.clear();
  m_is_shut = true;
}

