#include "hittable.h"
#include "hittableList.h"
#include "utilities.h"


bool HittableList::hit(const ray &ray, float tMin, float tMax, HitRecord &hitRecord)const
{
  HitRecord tmpRec{};
  float closestHit{tMax};
  bool isHit{false};

  for (const auto &object: objects)
  {
    if (object->hit(ray, tMin, closestHit, tmpRec))
    {
      isHit = true;
      closestHit = tmpRec.t;
      hitRecord = tmpRec;
    }
  }
  return isHit;
}
