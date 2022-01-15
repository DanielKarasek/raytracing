#ifndef triangle_sfkjlajk_h
#define triangle_sfkjlajk_h

#include "vec3.h"
#include "hittable.h"
#include "material.h"
#include "utilities.h"

class TriangleMeshHittable: public Hittable{

  public:
    TriangleMeshHittable(shared_ptr<Material> material):material{material}{}
    virtual bool hit(const ray &ray, float tMin, float tMax, HitRecord &hitRecord)const override;

  protected:
  
    shared_ptr<Material> material;
    

};


#endif