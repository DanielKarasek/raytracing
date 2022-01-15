#ifndef CAMERA_DFJA86_H
#define CAMERA_DFJA86_H
#include "utilities.h"
#include "vec3.h"

class Camera
{
  public:
    Camera(
      float fvow,
      float aspect_ratio,
      point3 lookfrom,
      point3 lookat,
      vec3 vup,
      float focal_distance,
      float aperture
    )
    {
      
      float radian_fvow = degree2radians(fvow);
      float h = tan(radian_fvow/2);
      
      float viewportHeight{2.f*h};
      float viewportWidth{viewportHeight*aspect_ratio};

      w = unit_vector(lookfrom-lookat);
      u = unit_vector(cross(vup, w));
      v = cross(w, u);
      

      cameraOrig = lookfrom;
      horizontal = u*focal_distance*viewportWidth;
      vertical = v*focal_distance*viewportHeight;

      lowerLeftCorner = point3(cameraOrig - horizontal/2 - vertical/2 - w*focal_distance);  
      lens_radius = aperture/2;
    }



    ray getRay(float s, float t)const
    {
      
      vec3 r = lens_radius * random_in_disk();
      vec3 offset = r.x()*u + r.y()*v;
      return {cameraOrig+offset,
              lowerLeftCorner + s*horizontal + t*vertical - cameraOrig-offset};

    }

  protected:
    point3 cameraOrig;
    vec3 horizontal;
    vec3 vertical;
    point3 lowerLeftCorner;
    vec3 w, u, v;
    float lens_radius;

};







#endif
