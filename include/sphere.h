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
    virtual bool hit(const ray &ray, float tMin, float tMax, HitRecord &hitRecord)const override;
  protected:
    float radius;
    point3 center;
    shared_ptr<Material> material;
};


#endif