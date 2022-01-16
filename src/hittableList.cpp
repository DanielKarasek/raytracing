#include "hittable.h"
#include "hittableList.h"
#include "utilities.h"


bool HittableList::hit(const Ray &ray, float t_min, float t_max, HitRecord &hit_record)const
{
  HitRecord tmp_rec{};
  float closest_hit{t_max};
  bool is_hit{false};

  for (const auto &object: objects)
  {
    if (object->hit(ray, t_min, closest_hit, tmp_rec))
    {
      is_hit = true;
      closest_hit = tmp_rec.t;
      hit_record = tmp_rec;
    }
  }
  return is_hit;
}
