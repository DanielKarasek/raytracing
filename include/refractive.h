#ifndef REFRACTIVE_DJFSK_H
#define REFRACTIVE_DJFSK_H

#include "material.h"
#include "ray.h"
#include "vec3.h"
#include "hittable.h"


class Refractive: public Material
{

  public:
    Refractive(double refraction_idx):refraction_idx{refraction_idx}{}
    virtual bool scatter(const Ray& ray_in, const HitRecord &rec, color &attenuation, Ray &scattered)const;
  protected:
    double refraction_idx;
    static double reflectance(double cosine, double ref_idx) 
    {
      // Use Schlick's approximation for reflectance.
      auto r0 = (1-ref_idx) / (1+ref_idx);
      r0 = r0*r0;
      return r0 + (1-r0)*pow((1 - cosine),5);
    }
};


#endif