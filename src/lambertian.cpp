#include "material.h"
#include "ray.h"
#include "vec3.h"
#include "hittable.h"
#include "lambertian.h"

bool Lambertian::scatter(const Ray& ray_in, const HitRecord &rec, color &attenuation, Ray &scattered)const
{
  vec3 direction = rec.unit_normal + random_unit_vec(); 
  scattered = Ray(rec.hit_point, direction);
  attenuation = albedo;
  return true;
}