#include <cmath>
#include "material.h"
#include "ray.h"
#include "vec3.h"
#include "hittable.h"
#include "refractive.h"

bool Refractive::scatter(const ray& ray_in, const HitRecord &rec, color &attenuation, ray &scattered)const
{
  double tmp_refraction = refractionIdx;
  vec3 vec_in_unit = unit_vector(ray_in.direction());
  if (!rec.frontFace)
    tmp_refraction = 1/refractionIdx;

  double cos_theta = std::fabs(dot(vec_in_unit, rec.unitNormal));
  double sin_theta = std::sqrt(1-cos_theta*cos_theta);
  
  if (sin_theta > 1 || reflectance(cos_theta, tmp_refraction) > getRandomFloat()) // cannot refract snell has no solution
    scattered = ray(rec.hitPoint, reflect(ray_in, rec.unitNormal));
  else
    scattered = ray(rec.hitPoint, refract(ray_in, rec.unitNormal, tmp_refraction));
  attenuation = {1.0, 1.0, 1.0};
  return true;
}