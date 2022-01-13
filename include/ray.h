#ifndef RAY_AHDJKA58190_H
#define RAY_AHDJKA58190_H
#include "vec3.h"

class ray{
  public:
    ray():orig{}, direc{}{}
    ray(const point3& origin, const vec3& direction):orig(origin), direc{direction}{}

    vec3 direction()const{return direc;}
    point3 origin()const{return orig;}

    point3 at(float t) const {return orig+t*direc;}

  protected:
    point3 orig;
    vec3 direc;
};

#endif