#include "material.h"
#include "ray.h"
#include "vec3.h"
#include "hittable.h"
#include "metal.h"

bool Metal::scatter(const Ray& ray_in, const HitRecord &rec, color &attenuation, Ray &scattered)const
{
  vec3 direction = reflect(ray_in, rec.unit_normal); 
  direction += random_in_sphere()*fuzziness;
  scattered = Ray(rec.hit_point, direction);
  attenuation = albedo;
  return dot(direction, rec.unit_normal)>0;
}