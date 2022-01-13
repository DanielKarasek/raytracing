#include <iostream>
#include <cmath>
#include "vec3.h"
#include "utilities.h"
std::ostream& operator<<(std::ostream &out, vec3 &v)
{
  out << v.e[0] << ' '
      << v.e[1] << ' ' 
      << v.e[2]; 
  return out;
}


vec3 operator+(const vec3 &u, const vec3 &v)
{
  return vec3{u.x()+v.x(), u.y()+v.y(), u.z()+v.z()};
}

vec3 operator-(const vec3 &u, const vec3 &v)
{
  return vec3{u.x()-v.x(), u.y()-v.y(), u.z()-v.z()};
}

vec3 operator*(const vec3 &u, float t)
{
  return vec3{u.x()*t, u.y()*t, u.z()*t};
}

vec3 operator*(float t, const vec3 &u)
{
  return vec3{u.x()*t, u.y()*t, u.z()*t};
}


vec3 operator*(const vec3 &u, const vec3& v)
{
  return vec3{u.x()*v.x(), u.y()*v.y(), u.z()*v.z()};
}

vec3 operator/(const vec3 &u, float t)
{
  return u*(1/t);
}

float dot(const vec3 &u, const vec3 &v)
{
  return u.x()*v.x() + u.y()*v.y() + u.z()*v.z();
}

vec3 cross(const vec3 &u, const vec3 &v)
{
  return vec3{u.y()*v.z() - u.z()*v.y(),
              u.z()*v.x() - u.x()*v.z(),
              u.x()*v.y() - u.y()*v.x()};
}

vec3 unit_vector(const vec3 &v)
{
  return v/v.lenght();
}


vec3 randomVector()
{
  return {getRandomFloat(), getRandomFloat(), getRandomFloat()};
}

vec3 randomVector(float min, float max)
{
  return randomVector()*(max-min)+vec3(min, min, min);
}

vec3 randomInSphere()
{
  vec3 vect = randomVector(-1, 1);
  while (vect.lenght_squared() > 1)
    vect = randomVector(-1, 1);
  return vect;
}

vec3 random_in_disk()
{
  vec3 vect;
  while(true)
  {
    vect = vec3(getRandomFloat(), getRandomFloat(), 0);
    vect = vect * 2 - vec3(1, 1, 0);
    if (vect.lenght()>1) continue;
    return vect;
  }
}

vec3 randomUnitVec()
{
  return unit_vector(randomInSphere());
}


vec3 refract(const ray &ray_in, const vec3 &normal, double refractionCoefficient)
{
  vec3 vec_in = unit_vector(ray_in.direction());
  double cos = std::fmin(dot(normal, - vec_in), 1);
  vec3 perpendicular = refractionCoefficient*(vec_in + cos*normal);
  vec3 parralel = -std::sqrt(std::fabs(1-perpendicular.lenght_squared()))*normal;
  // std::cerr << ray_in << '\n' << perpendicular << '\n' << parralel << '\n' << "____________________\n";
  return perpendicular + parralel;
}

vec3 reflect(const ray &ray_in, const vec3 &normal)
{
  return ray_in.direction() - 2*dot(ray_in.direction(), normal)*normal; 
}
