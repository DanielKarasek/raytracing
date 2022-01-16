#ifndef COLOR_ASFJAKJ546DA_H
#define COLOR_ASFJAKJ546DA_H
#include <iostream>
#include <algorithm>
#include "vec3.h"

void write_color(std::ostream& os, const color &c, int samples)
{
  float r = c.x();
  float g = c.y();
  float b = c.z();
  
  // float scale = 1.0/samples;
  
  r = sqrt(r/samples);
  g = sqrt(g/samples);
  b = sqrt(b/samples);

  r = std::clamp(r, 0.f, 0.999f);
  g = std::clamp(g, 0.f, 0.999f);
  b = std::clamp(b, 0.f, 0.999f);


  
  os << static_cast<int>(r*256) << ' '
     << static_cast<int>(g*256) << ' '
     << static_cast<int>(b*256) << ' ';
}

#endif