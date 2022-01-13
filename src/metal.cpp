#include "material.h"
#include "ray.h"
#include "vec3.h"
#include "hittable.h"
#include "metal.h"

bool Metal::scatter(const ray& ray_in, const HitRecord &rec, color &attenuation, ray &scattered)const
{
  vec3 direction = reflect(ray_in, rec.unitNormal); 
  direction += randomInSphere()*fuzziness;
  scattered = ray(rec.hitPoint, direction);
  attenuation = albedo;
  return dot(direction, rec.unitNormal)>0;
}