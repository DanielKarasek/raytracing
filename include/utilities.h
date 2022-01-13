#ifndef UTILITIES_SDFJKSDHK_H
#define UTILITIES_SDFJKSDHK_H

#include <memory>
#include <limits>
#include <cmath>

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

inline constexpr double infinity = std::numeric_limits<double>::infinity();
inline constexpr double pi = 3.1415926535897932385;


float degree2radians(float degree);

float radians2degree(float radians);

float getRandomFloat();

float getRandomFloat(float min, float max);
//
#include <vec3.h>
#include <ray.h>


#endif

