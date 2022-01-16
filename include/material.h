#ifndef MATERIAL_SFSJDKLFJS12142_H
#define MATERIAL_SFSJDKLFJS12142_H

#include "ray.h"
#include "vec3.h"
#include "hittable.h"

class Material
{

  public:
    virtual bool scatter(const Ray& ray_in, const HitRecord& hit_rec, color &attenuation, Ray& scattered)const = 0;



};


#endif