#include "vec3.h"
#include "ray.h"
#include "triangle_obj.h"
#include "bunny.h"

vec3 triangles[] = {{-1,-1,-1}, {1,-1,-1}, {0,1,-1}, {1,-1,-1}, {2,0.5,-1},{0,1,-1}};


bool TriangleMeshHittable::hit(const ray &ray, float tMin, float tMax, HitRecord &hitRecord)const
{
  double tmp_t;
  double t_closest = tMax;
  double u, v;
  bool hit_something {false};

  vec3 closest_normal;
  for (int triangle_cnt=0; triangle_cnt < 4968; ++triangle_cnt){
    vec3 v0 = bunny[faces[triangle_cnt][0]-1]*20 - vec3{0,1.2,0};
    vec3 v1 = bunny[faces[triangle_cnt][1]-1]*20 - vec3{0,1.2,0};
    vec3 v2 = bunny[faces[triangle_cnt][2]-1]*20 - vec3{0,1.2,0};
    vec3 edge0 = v1-v0;
    vec3 edge1 = v2-v1;
    vec3 edge2 = v0-v2;
    vec3 normal = cross(edge0, -edge2);

    double length_norm = normal.lenght_squared();
    // p0 = bunny[faces[triangle_cnt][0]]
    // p1 = orig+t*dir;
    // (p1-p0).n = 0
    // t = -orig.n+bunny[faces[triangle_cnt][0]].n/dir.n
    double denom = dot(ray.direction(), normal); 
    
    if (std::abs(denom) < -1e-6) continue;

    double nom = -dot(ray.origin(), normal) + dot(v0, normal);
    tmp_t = nom/denom;
    if (tmp_t < 0 || tmp_t < tMin || tmp_t > tMax || tmp_t > t_closest) continue;
    
    // get hit point
    vec3 hit_point = ray.origin() + tmp_t*ray.direction();
    
    vec3 C; // inside-outside test


    C = cross(edge0, hit_point - v0);
    if (dot(C, normal) < 0) continue;
    
    C = cross(edge1, hit_point - v1);
    if ((u=dot(C, normal)) < 0) continue;
    
    C = cross(edge2, hit_point - v2);
    if ((v=dot(C, normal)) < 0) continue;
    
    u /= length_norm;
    v /= length_norm;
    hit_something = true;
    closest_normal = normal;
    t_closest = tmp_t;

  }
  if (!hit_something) return false;
  hitRecord.hitPoint = ray.origin() + t_closest*ray.direction();
  hitRecord.material = this->material;
  hitRecord.t = t_closest;
  hitRecord.setFrontFace(ray, unit_vector(closest_normal));
  return true;
}

