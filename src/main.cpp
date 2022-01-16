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
      float choose_mat = getRandomFloat();
      point3 center(a + 0.9*getRandomFloat(), 0.2, b + 0.9*getRandomFloat());

      if ((center - point3(4, 0.2, 0)).lenght() > 0.9) 
      {
        shared_ptr<Material> sphere_material;

        if (choose_mat < 0.8) 
        {
            // diffuse
            auto albedo = randomVector(0,1) * randomVector(0,1);
            sphere_material = make_shared<Lambertian>(albedo);
            world.add(make_shared<Sphere>(0.2, center, sphere_material));
        } 
        else if (choose_mat < 0.95) 
        {
          // metal
          auto albedo = randomVector(0.5,1);
          auto fuzz = getRandomFloat(0, 0.5);
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

color rayColor(const ray& r, const HittableList &world, double depth)
{
  HitRecord rec;
  
  if (depth <= 0) return {0, 0, 0};

  if (world.hit(r, 0.001, infinity, rec))
  {
    ray scattered;
    color attenuation;
    if (rec.material->scatter(r, rec, attenuation, scattered))
      return attenuation * rayColor(scattered, world, depth-1);  
    else return {0, 0, 0};
  }
  auto unitDirection = unit_vector(r.direction());
  auto t = 0.5*(unitDirection.y()+1.0);
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
  for (int sampledCount{0}; sampledCount<samples_per_pixel; sampledCount++)
  {
    double u = static_cast<double>(col+getRandomFloat())/(im_width-1);
    double v = static_cast<double>(row+getRandomFloat())/(im_height-1);
    
    ray r = cam.getRay(u, v);
    c += rayColor(r, world, max_depth);
  }
  // std::cerr << row << ' ' << col << ' ' << im_width  << ' ' << (row-1)*im_width + col<<'\n';
  arr[col] = c;
}

int main(int argc, char *argv[])
{
  
  // IMAGE
  const float aspect_ratio = 3.f/2.f;
  const int imageWidth{1920};
  const int imageHeight{static_cast<int>(imageWidth/aspect_ratio)};
  const int samplePerPixel{5};
  const int maxDepth{20};

  // // WORLD
  HittableList worldObjects(5);

  auto materialGround = make_shared<Lambertian>(color(0.8, 0.8, 0.0));
  auto materialCenter = make_shared<Lambertian>(color(0.7, 0.3, 0.3));
  auto materialLeft = make_shared<Refractive>(1.5);
  auto materialRight = make_shared<Metal>(color(0.8, 0.6, 0.2), 0.2);
  worldObjects.add(make_shared<Sphere>(100, point3(0,-100.5,-1), materialGround));
  // worldObjects.add(make_shared<Sphere>(0.5, point3(0,0,-1), materialCenter));
  worldObjects.add(make_shared<Sphere>(0.5, point3(-2,0,1), materialCenter));
  // worldObjects.add(make_shared<Sphere>(-0.4, point3(-1,0,-1), materialLeft));
  // worldObjects.add(make_shared<Sphere>(0.5, point3(1,0,-1), materialRight));
  worldObjects.add(make_shared<TriangleMeshHittable>(materialRight));

  // HittableList worldObjects = make_world();
  // CAMERA
  float vfov = 60;
  point3 lookfrom{0, 0, 5};
  point3 lookat{0, 0.07, 0};
  point3 vup{0,1,0};
  float distance = (lookfrom-lookat).lenght();
  float lens_radius = 0.0001;
  Camera cam{vfov, aspect_ratio, lookfrom, lookat, vup, distance, lens_radius};
  
  std::array<color, imageWidth> rendered_image;
  std::function<void(int, int)> job{[&rendered_image, imageWidth, imageHeight, maxDepth, samplePerPixel, &cam, &worldObjects](int col, int row)
                        {
                          get_single_val<imageWidth>(rendered_image, imageWidth, imageHeight, maxDepth, col, row, samplePerPixel, cam, worldObjects);
                        }};
  
  ThreadPool pool{};
  
  std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

  for (int row{imageHeight}; row>0; --row)
  {
    std::cerr << "\rScanlines remaining: " << row << '\n' << std::flush;
    for (int col{0}; col<imageWidth; ++col)
    {
      std::function<void()> concrete_job {[job, col, row](){job(col, row);}};
      pool.add_job(concrete_job);

      // writeColor(std::cout, c, samplePerPixel);
    }
    while(pool.any_jobs());
    for (auto &col : rendered_image)
    {
      writeColor(std::cout, col, samplePerPixel);
    }
    std::cout << '\n';
  }

  pool.shutdown();
  std::cerr << "done";
  
  return 0;
}


// bool hit_triangle(ray &r,vec3 u0, vec3 u1, vec3 u2, double &u, double &v, double &t, bool single_sided)
// {
//   vec3 edge0 = u1-u0;
//   vec3 edge1 = u2-u1;
//   vec3 edge2 = u0-u2;
//   vec3 normal = cross(edge0, -edge2);
//   double length_norm = normal.lenght_squared();
//   // p0 = u0
//   // p1 = orig+t*dir;
//   // (p1-p0).n = 0
//   // t = -orig.n+u0.n/dir.n
//   double denom = dot(r.direction(), normal); 
  

//   if (denom > -1e-6) return false;

//   double nom = -dot(r.origin(), normal) + dot(u0, normal);
//   t = nom/denom;
  
//   if (t<0) return false; //ray behind
  
//   // get hit point
//   vec3 hit_point = r.origin() + t*r.direction();
  
//   vec3 C; // inside-outside test


//   C = cross(edge0, hit_point - u0);
//   if (dot(C, normal) < 0) return false;
  
//   C = cross(edge1, hit_point - u1);
//   if ((u=dot(C, normal)) < 0) return false;
  
//   C = cross(edge2, hit_point - u2);
//   if ((v=dot(C, normal)) < 0) return false;
  
//   u /= length_norm;
//   v /= length_norm;
 
//   return true;
// }

// int main()
// {
//   vec3 u0{-1, -2, -5};
//   vec3 u1{4, -1, -5};
//   vec3 u2{0, 1, -5};
//   color v0_col{1, 0, 0};
//   color v1_col{0, 1, 0};
//   color v2_col{0, 0, 1};
//   // double t;
//   // double u; // how much A
//   // double v; // how much B

//   int width = 400;
//   int height = width*2./3.;

//   float viewport_dist{1};
//   float viewport_width {2};
//   float viewport_height {2*2./3.};
  
//   vec3 vertical{0, viewport_height, 0};
//   vec3 horizontal{viewport_width, 0, 0};
//   vec3 bottom_left{-viewport_width/2, -viewport_height/2, 0};

//   vec3 origin{0,0,0};

//   auto diffuse = make_shared<Lambertian>(color(0.7, 0.3, 0.3));
//   TriangleMeshHittable test_mesh(diffuse);
//   HitRecord tmp_record;

//   std::cout << "P3\n" << width << ' ' << height << "\n255\n";
//   // std::cout <<  tmp;
//   for (int r=height-1; r>=0; --r)
//   {
//     for (int c=0; c<width; ++c)
//     {
//       double step_c = c/static_cast<double>(width-1);
//       double step_r = r/static_cast<double>(height-1);
      
//       vec3 dir = bottom_left + horizontal*step_c + vertical*step_r + vec3(0,0,-viewport_dist)-origin; 
//       ray r{origin, dir};
//       color col{0, 0, 0};
//       // std::cout << dir << '\n';
//       color attenuation;
//       ray scattered;
//       if (test_mesh.hit(r, 0, infinity, tmp_record))
//       {
//         tmp_record.material->scatter(r, tmp_record, attenuation, r);
//         col = attenuation;
//         // std::cout << u << ' ' << v << '\n';
//         //std::cout << col;
//       }
//       writeColor(std::cout, col, 1);
//     }
//     std::cout << '\n';
//   }
// }