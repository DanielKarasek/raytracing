#ifndef MATERIAL_SFSJDKLFJS12142_H
#define MATERIAL_SFSJDKLFJS12142_H

#include "ray.h"
#include "vec3.h"
#include "hittable.h"

class Material
{

  public:
    virtual bool scatter(const ray& ray_in, const HitRecord& hitRec, color &attenuation, ray& scattered)const = 0;



};


#endif