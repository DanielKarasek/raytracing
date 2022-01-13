#include "material.h"
#include "ray.h"
#include "vec3.h"
#include "hittable.h"
#include "lambertian.h"

bool Lambertian::scatter(const ray& ray_in, const HitRecord &rec, color &attenuation, ray &scattered)const
{
  vec3 direction = rec.unitNormal + randomUnitVec(); 
  scattered = ray(rec.hitPoint, direction);
  attenuation = albedo;
  return true;
}