#include <cmath>
#include "material.h"
#include "ray.h"
#include "vec3.h"
#include "hittable.h"
#include "refractive.h"

bool Refractive::scatter(const Ray& ray_in, const HitRecord &rec, color &attenuation, Ray &scattered)const
{
  double tmp_refraction = refraction_idx;
  vec3 vec_in_unit = unit_vector(ray_in.direction());

  if (!rec.front_face)
    tmp_refraction = 1/refraction_idx;

  double cos_theta = std::fabs(dot(vec_in_unit, rec.unit_normal));
  double sin_theta = std::sqrt(1-cos_theta*cos_theta);
  
  if (sin_theta > 1 || reflectance(cos_theta, tmp_refraction) > get_random_float()) // cannot refract snell has no solution
    scattered = Ray(rec.hit_point, reflect(ray_in, rec.unit_normal));
  else
    scattered = Ray(rec.hit_point, refract(ray_in, rec.unit_normal, tmp_refraction));
  attenuation = {1.0, 1.0, 1.0};
  return true;
}