#ifndef RAYTRACER_HITTABLE_H
#define RAYTRACER_HITTABLE_H

#include "Maths/Ray.h"
#include "HitResult.h"

namespace RayTracer {

    class Hittable {
    public:
        virtual ~Hittable() = default;
        virtual bool Hit(const Ray& ray, Interval interval, HitResult& result) const = 0;
    };

}

#endif //RAYTRACER_HITTABLE_H
