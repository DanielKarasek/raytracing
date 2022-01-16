#include <random>
#include "utilities.h"


float degree2radians(float degree)
{
  return pi*degree/180;
}

float radians2degree(float radians)
{
  return 180*radians/pi;
}

float get_random_float()
{
  static std::mt19937 mt;
  static std::uniform_real_distribution<double> gen(0,1);
  return gen(mt);
}

float get_random_float(float min, float max)
{
  return get_random_float()*(max-min)+min;
}