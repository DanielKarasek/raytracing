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
      
      float viewport_height{2.f*h};
      float viewport_width{viewport_height*aspect_ratio};

      w = unit_vector(lookfrom-lookat);
      u = unit_vector(cross(vup, w));
      v = cross(w, u);
      

      camera_orig = lookfrom;
      horizontal = u*focal_distance*viewport_width;
      vertical = v*focal_distance*viewport_height;

      lower_left_corner = point3(camera_orig - horizontal/2 - vertical/2 - w*focal_distance);  
      lens_radius = aperture/2;
    }



    Ray get_ray(float s, float t)const
    {
      
      vec3 r = lens_radius * random_in_disk();
      vec3 offset = r.x()*u + r.y()*v;
      return {camera_orig+offset,
              lower_left_corner + s*horizontal + t*vertical - camera_orig-offset};

    }

  protected:
    point3 camera_orig;
    vec3 horizontal;
    vec3 vertical;
    point3 lower_left_corner;
    vec3 w, u, v;
    float lens_radius;

};







#endif
