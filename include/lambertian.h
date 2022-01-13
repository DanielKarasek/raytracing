#ifndef LAMBERTIAN_DJFSK_H
#define LAMBERTIAN_DJFSK_H

#include "material.h"
#include "ray.h"
#include "vec3.h"
#include "hittable.h"


class Lambertian: public Material
{

  public:
    Lambertian(color albedo):albedo{albedo}{}
    virtual bool scatter(const ray& ray_in, const HitRecord &rec, color &attenuation, ray &scattered)const;
  protected:
    color albedo;
};


#endif