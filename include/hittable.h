#ifndef HITTABLE_ASKFHALJ_H
#define HITTABLE_ASKFHALJ_H
#include "vec3.h"
#include "ray.h"
#include "utilities.h"

class Material;

struct HitRecord
{
  point3 hitPoint;
  vec3 unitNormal;
  float t;

  shared_ptr<Material> material;

  bool frontFace;
  void setFrontFace(const ray& ray, const vec3& outNormal)
  {
    frontFace = dot(ray.direction(), outNormal)>=0;
    unitNormal = frontFace ? -outNormal : outNormal;
  }
};


class Hittable
{
  public:
    virtual bool hit(const ray &ray, float tMin, float tMax, HitRecord &hitRecord)const = 0;
};


#endif