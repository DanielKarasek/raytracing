#include <iostream>
#include <fstream>
#include <cmath>
#include <array>

#include "hittable.h"
#include "utilities.h"
#include "auxilaries.h"

#include "hittableList.h"

#include "camera.h"
#include "color.h"
#include "sphere.h"
#include "triangle_obj.h"

#include "lambertian.h"
#include "metal.h"
#include "refractive.h"

#include "thread_pool.h"

HittableList make_world()
{
  HittableList world;

  auto ground_material = make_shared<Lambertian>(color(0.5, 0.5, 0.5));
  world.add(make_shared<Sphere>(1000, point3(0,-1000,0), ground_material));

  for (int a = -11; a < 11; a++) 
  {
    for (int b = -11; b < 11; b++) 
    {
      float choose_mat = get_random_float();
      point3 center(a + 0.9*get_random_float(), 0.2, b + 0.9*get_random_float());

      if ((center - point3(4, 0.2, 0)).lenght() > 0.9) 
      {
        shared_ptr<Material> sphere_material;

        if (choose_mat < 0.8) 
        {
            // diffuse
            auto albedo = random_vector(0,1) * random_vector(0,1);
            sphere_material = make_shared<Lambertian>(albedo);
            world.add(make_shared<Sphere>(0.2, center, sphere_material));
        } 
        else if (choose_mat < 0.95) 
        {
          // metal
          auto albedo = random_vector(0.5,1);
          auto fuzz = get_random_float(0, 0.5);
          sphere_material = make_shared<Metal>(albedo, fuzz);
          world.add(make_shared<Sphere>(0.2, center, sphere_material));
        } 
        else 
        {
          // glass
          sphere_material = make_shared<Refractive>(1.5);
          world.add(make_shared<Sphere>(0.2, center, sphere_material));
        }
      }
    }
  }

  auto material1 = make_shared<Refractive>(1.5);
  world.add(make_shared<Sphere>(1.0, point3(0, 1, 0), material1));

  auto material2 = make_shared<Lambertian>(color(0.4, 0.2, 0.1));
  world.add(make_shared<Sphere>(1.0, point3(-4, 1, 0), material2));

  auto material3 = make_shared<Metal>(color(0.7, 0.6, 0.5), 0.0);
  world.add(make_shared<Sphere>(1.0, point3(4, 1, 0), material3));

  return world;
}

color ray_color(const Ray& r, const HittableList &world, double depth)
{
  HitRecord rec;
  
  if (depth <= 0) return {0, 0, 0};

  if (world.hit(r, 0.001, infinity, rec))
  {
    Ray scattered;
    color attenuation;
    if (rec.material->scatter(r, rec, attenuation, scattered))
      return attenuation * ray_color(scattered, world, depth-1);  
    else return {0, 0, 0};
  }
  auto unit_direction = unit_vector(r.direction());
  auto t = 0.5*(unit_direction.y()+1.0);
  return (1.0-t)*color(1., 1., 1.) + t*color(0.5, 0.7, 1.0);
}

template<size_t n>
void get_single_val(std::array<color, n> &arr,
                    int im_width,
                    int im_height,
                    int max_depth,
                    int col,
                    int row, 
                    int samples_per_pixel,
                    const Camera &cam, 
                    HittableList &world)
{
  color c{0, 0, 0};
  for (int sampled_count{0}; sampled_count<samples_per_pixel; sampled_count++)
  {
    double u = static_cast<double>(col+get_random_float())/(im_width-1);
    double v = static_cast<double>(row+get_random_float())/(im_height-1);
    
    Ray r = cam.get_ray(u, v);
    c += ray_color(r, world, max_depth);
  }
  // std::cerr << row << ' ' << col << ' ' << im_width  << ' ' << (row-1)*im_width + col<<'\n';
  arr[col] = c;
}

int main(int argc, char *argv[])
{
  
  // IMAGE
  const float aspect_ratio = 3.f/2.f;
  const int image_width{1920};
  const int image_height{static_cast<int>(image_width/aspect_ratio)};
  const int samples_per_pixel{5};
  const int max_depth{20};

  // // WORLD
  HittableList world_object_list(5);

  auto material_ground = make_shared<Lambertian>(color(0.8, 0.8, 0.0));
  auto material_center = make_shared<Lambertian>(color(0.7, 0.3, 0.3));
  auto material_left = make_shared<Refractive>(1.5);
  auto material_right = make_shared<Metal>(color(0.8, 0.6, 0.2), 0.2);
  world_object_list.add(make_shared<Sphere>(100, point3(0,-100.5,-1), material_ground));
  // worldObjects.add(make_shared<Sphere>(0.5, point3(0,0,-1), materialCenter));
  world_object_list.add(make_shared<Sphere>(0.5, point3(-2,0,1), material_center));
  // worldObjects.add(make_shared<Sphere>(-0.4, point3(-1,0,-1), materialLeft));
  // worldObjects.add(make_shared<Sphere>(0.5, point3(1,0,-1), materialRight));
  world_object_list.add(make_shared<TriangleMeshHittable>(material_right));

  // HittableList worldObjects = make_world();
  // CAMERA
  float vfov = 60;
  point3 lookfrom{0, 0, 5};
  point3 lookat{0, 0.07, 0};
  point3 vup{0,1,0};
  float distance = (lookfrom-lookat).lenght();
  float lens_radius = 0.0001;
  Camera cam{vfov, aspect_ratio, lookfrom, lookat, vup, distance, lens_radius};
  
  std::array<color, image_width> rendered_line;
  std::function<void(int, int)> job{[&rendered_line, image_width, image_height, max_depth, samples_per_pixel, &cam, &world_object_list](int col, int row)
                        {
                          get_single_val<image_width>(rendered_line, image_width, image_height, max_depth, col, row, samples_per_pixel, cam, world_object_list);
                        }};
  
  ThreadPool pool{};
  
  std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

  for (int row{image_height}; row>0; --row)
  {
    std::cerr << "\rScanlines remaining: " << row << '\n' << std::flush;
    for (int col{0}; col<image_width; ++col)
    {
      std::function<void()> concrete_job {[job, col, row](){job(col, row);}};
      pool.add_job(concrete_job);

      // writeColor(std::cout, c, samplePerPixel);
    }
    while(pool.any_jobs());
    for (auto &col : rendered_line)
    {
      write_color(std::cout, col, samples_per_pixel);
    }
    std::cout << '\n';
  }

  pool.shutdown();
  std::cerr << "done";
  
  return 0;
}