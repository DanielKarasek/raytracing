#ifndef VEC3_231q23131q_H
#define VEC3_231q23131q_H
#include <iostream>
#include <cmath>

class vec3{
  public:
    vec3(): e{0, 0, 0}{}
    vec3(float e0, float e1, float e2): e{e0, e1, e2}{}
    vec3(const vec3 &vec):e{vec.e[0], vec.e[1], vec.e[2]}{}

    float x() const {return e[0];}
    float y() const {return e[1];}
    float z() const {return e[2];}

    vec3 operator-()const{return vec3(-e[0], -e[1], -e[2]);};
    float operator[](int i)const{return e[i];}
    float &operator[](int i){return e[i];}

    vec3& operator+=(const vec3 &v)
    {
      e[0] += v.e[0];
      e[1] += v.e[1];
      e[2] += v.e[2];
      return *this;
    }

    vec3& operator*=(const float t)
    {
      e[0] *= t;
      e[1] *= t;
      e[2] *= t;
      return *this;
    }

    vec3& operator/=(const float t)
    {
      return *this *= 1/t;
    }

    double lenght()const
    {
      return std::sqrt(lenght_squared());
    }

    double lenght_squared() const
    {
      return e[0]*e[0]+e[1]*e[1]+e[2]*e[2];
    }
  protected:
    float e[3];
  friend std::ostream& operator<<(std::ostream &out, vec3 &v);
};

std::ostream& operator<<(std::ostream &out, vec3 &v);
vec3 operator+(const vec3 &u, const vec3 &v);
vec3 operator-(const vec3 &u, const vec3 &v);
vec3 operator*(const vec3 &u, float t);
vec3 operator*(float t, const vec3 &u);
vec3 operator*(const vec3 &u, const vec3& v);
vec3 operator/(const vec3 &u, float t);
float dot(const vec3 &u, const vec3 &v);
vec3 cross(const vec3 &u, const vec3 &v);
vec3 unit_vector(const vec3 &v);
vec3 randomVector();
vec3 randomVector(float min, float max);
vec3 randomInSphere();
vec3 randomUnitVec();

vec3 random_in_disk();

class ray;

vec3 refract(const ray &ray_in, const vec3 &normal, double refractionCoefficient);
vec3 reflect(const ray &ray_in, const vec3 &normal);

using point3 = vec3;
using color = vec3;


#endif