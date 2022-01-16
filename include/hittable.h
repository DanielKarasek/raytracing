#ifndef HITTABLE_ASKFHALJ_H
#define HITTABLE_ASKFHALJ_H
#include "vec3.h"
#include "ray.h"
#include "utilities.h"

class Material;

struct HitRecord
{
  point3 hit_point;
  vec3 unit_normal;
  float t;

  shared_ptr<Material> material;

  bool front_face;
  void setFrontFace(const Ray& ray, const vec3& out_normal)
  {
    front_face = dot(ray.direction(), out_normal)>=0;
    unit_normal = front_face ? -out_normal : out_normal;
  }
};


class Hittable
{
  public:
    virtual bool hit(const Ray &ray, float t_min, float t_max, HitRecord &hit_record)const = 0;
};


#endif