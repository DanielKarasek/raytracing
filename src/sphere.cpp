#include "vec3.h"
#include "hittable.h"
#include "sphere.h"
#include "material.h"

bool Sphere::hit(const Ray &ray, float t_min, float t_max, HitRecord &hit_record)const
{
  vec3 oc = ray.origin()-center;
  auto a = ray.direction().lenght_squared();
  auto half_b = dot(ray.direction(), oc);
  auto c = dot(oc, oc) - radius*radius;
  auto determinant = half_b*half_b - a*c;
  if (determinant < 0)
    return false;
  auto sqrtd = sqrt(determinant);
  auto root = (-half_b - sqrtd)/a;
  if (root < t_min || t_max < root)
  { 
    root = (-half_b+sqrtd)/a;
    if (root < t_min || t_max < root)
      return false;
  }
  auto hitPoint = ray.at(root);
  auto normal = (hitPoint - center)/radius;
  hit_record.setFrontFace(ray, normal);
  hit_record.hit_point = hitPoint;
  hit_record.t = root;
  hit_record.material = material;
  return true;
}