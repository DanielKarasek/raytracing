#include <iostream>
#include <fstream>
#include <cmath>
#include "hittable.h"
#include "utilities.h"
#include "auxilaries.h"

#include "hittableList.h"

#include "camera.h"
#include "color.h"
#include "sphere.h"

#include "lambertian.h"
#include "metal.h"
#include "refractive.h"

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

int main(int argc, char *argv[])
{
  
  // IMAGE
  float aspect_ratio = 3.f/2.f;
  const int imageWidth{400};
  const int imageHeight{static_cast<int>(imageWidth/aspect_ratio)};
  const int samplePerPixel{10};
  const int maxDepth{5};

  // // WORLD
  // HittableList worldObjects(5);

  // auto materialGround = make_shared<Lambertian>(color(0.8, 0.8, 0.0));
  // auto materialCenter = make_shared<Lambertian>(color(0.7, 0.3, 0.3));
  // auto materialLeft = make_shared<Refractive>(1.5);
  // auto materialRight = make_shared<Metal>(color(0.8, 0.6, 0.2), 1);
  // worldObjects.add(make_shared<Sphere>(100, point3(0,-100.5,-1), materialGround));
  // worldObjects.add(make_shared<Sphere>(0.5, point3(0,0,-1), materialCenter));
  // worldObjects.add(make_shared<Sphere>(0.5, point3(-1,0,-1), materialLeft));
  // worldObjects.add(make_shared<Sphere>(-0.4, point3(-1,0,-1), materialLeft));
  // worldObjects.add(make_shared<Sphere>(0.5, point3(1,0,-1), materialRight));


  HittableList worldObjects = make_world();
  // CAMERA
  float vfov = 20;
  point3 lookfrom{13, 2, 3};
  point3 lookat{0, 0, 0};
  point3 vup{0,1,0};
  float distance = (lookfrom-lookat).lenght();
  float lens_radius = 0.1;
  Camera cam{vfov, aspect_ratio, lookfrom, lookat, vup, distance, lens_radius};
  
  // RENDER
  // std::ofstream outImageFile;

  // outImageFile.open("outImage.PPM");
  
  std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

  for (int row{imageHeight}; row>0; --row)
  {
    std::cerr << "\rScanlines remaining: " << row << '\n' << std::flush;
    for (int col{0}; col<imageWidth; ++col)
    {
      color c {0, 0, 0};
      for (int sampledCount{0}; sampledCount<samplePerPixel; sampledCount++)
      {
        double u = static_cast<double>(col+getRandomFloat())/(imageWidth-1);
        double v = static_cast<double>(row+getRandomFloat())/(imageHeight-1);
        
        ray r = cam.getRay(u, v);
        c += rayColor(r, worldObjects, maxDepth);
      }
      writeColor(std::cout, c, samplePerPixel);
    }
    std::cout << '\n';
  }
  std::cerr << "done";
  // outImageFile.close();

  //output_image();
  return 0;
}