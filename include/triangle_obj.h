#ifndef triangle_sfkjlajk_h
#define triangle_sfkjlajk_h

#include "vec3.h"
#include "hittable.h"
#include "material.h"
#include "utilities.h"

class TriangleMeshHittable: public Hittable{

  public:
    TriangleMeshHittable(shared_ptr<Material> material):material{material}{}
    virtual bool hit(const Ray &ray, float t_min, float t_max, HitRecord &hit_record)const override;

  protected:
  
    shared_ptr<Material> material;
    

};


#endif