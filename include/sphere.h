#ifndef SPHERE_jshakjdfshak_H
#define SPHERE_jshakjdfshak_H

#include "hittable.h"
#include "vec3.h"
#include "ray.h"
#include "utilities.h"
#include "material.h"

class Sphere: public Hittable
{
  public:
    Sphere(float radius, point3 center, shared_ptr<Material> material):radius{radius}, center{center}, material{material}{}
    virtual bool hit(const Ray &ray, float t_min, float t_max, HitRecord &hit_record)const override;
  protected:
    float radius;
    point3 center;
    shared_ptr<Material> material;
};


#endif