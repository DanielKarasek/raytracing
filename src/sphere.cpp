#include "vec3.h"
#include "hittable.h"
#include "sphere.h"
#include "material.h"

bool Sphere::hit(const ray &ray, float tMin, float tMax, HitRecord &hitRecord)const
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
  if (root < tMin || tMax < root)
  { 
    root = (-half_b+sqrtd)/a;
    if (root < tMin || tMax < root)
      return false;
  }
  auto hitPoint = ray.at(root);
  auto normal = (hitPoint - center)/radius;
  hitRecord.setFrontFace(ray, normal);
  hitRecord.hitPoint = hitPoint;
  hitRecord.t = root;
  hitRecord.material = material;
  return true;
}