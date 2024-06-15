#ifndef RAYTRACER_HITTABLE_H
#define RAYTRACER_HITTABLE_H

#include "Maths/Ray.h"
#include "HitResult.h"
#include "Maths/AABB.h"

namespace RayTracer
{
    class IHittable
    {
    public:
        virtual ~IHittable() = default;
        virtual bool Hit(const Ray& ray, Interval interval, HitResult& result) const = 0;
        [[nodiscard]] virtual AABB BoundingBox() const = 0;
    };
}

#endif //RAYTRACER_HITTABLE_H
