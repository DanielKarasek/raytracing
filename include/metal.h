#ifndef METAL_BRNRRRR655_H
#define METAL_BRNRRRR655_H

#include "material.h"
#include "ray.h"
#include "vec3.h"
#include "hittable.h"


class Metal: public Material
{

  public:
    Metal(color albedo, double fuzziness):albedo{albedo}, fuzziness{fuzziness}{}
    virtual bool scatter(const ray& ray_in, const HitRecord &rec, color &attenuation, ray &scattered)const;
  protected:
    color albedo;
    double fuzziness;
};


#endif