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

float getRandomFloat()
{
  static std::mt19937 mt;
  static std::uniform_real_distribution<double> gen(0,1);
  return gen(mt);
}

float getRandomFloat(float min, float max)
{
  return getRandomFloat()*(max-min)+min;
}