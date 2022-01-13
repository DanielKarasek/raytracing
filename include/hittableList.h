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
    HittableList(int expectedCount){objects.reserve(expectedCount);}
    virtual bool hit(const ray &ray, float tMin, float tMax, HitRecord &hitRecord)const override;
    void add(shared_ptr<Hittable> obj){objects.emplace_back(obj);}
  protected:
    std::vector<shared_ptr<Hittable>> objects;
  
};

#endif