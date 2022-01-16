#ifndef HITTABLELIST_SDJFSKFH_H
#define HITTABLELIST_SDJFSKFH_H
#include "vector"
#include "vec3.h"
#include "ray.h"
#include "hittable.h"
#include "utilities.h"


class HittableList: public Hittable
{

  public:
    HittableList(){}
    HittableList(int expected_count){objects.reserve(expected_count);}
    virtual bool hit(const Ray &ray, float t_min, float t_max, HitRecord &hit_record)const override;
    void add(shared_ptr<Hittable> obj){objects.emplace_back(obj);}
  protected:
    std::vector<shared_ptr<Hittable>> objects;
  
};

#endif