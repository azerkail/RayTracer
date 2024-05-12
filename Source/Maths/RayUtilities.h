#ifndef RAYTRACER_RAYUTILITIES_H
#define RAYTRACER_RAYUTILITIES_H

#include <cmath>

#include "Vector3.h"
#include "Ray.h"

namespace RayTracer {

    inline float HitSphere(const Point3& center, float radius, const Ray& ray) {
        Vector3 origin = center - ray.Origin();
        float a = RayTracer::Dot(ray.Direction(), ray.Direction());
        float b = -2.0f * RayTracer::Dot(ray.Direction(), origin);
        float c = RayTracer::Dot(origin, origin) - radius * radius;
        float discriminant = b * b - 4 * a * c;

        if (discriminant < 0) {
            return -1;
        }

        return (-b - std::sqrt(discriminant)) / (2 * a);
    }

    inline Color GetRayColor(const Ray& ray) {
        auto raycast = RayTracer::HitSphere(Point3{0, 0, -1}, 0.5, ray);
        if (raycast > 0) {
            Vector3 raycastUnitDirection = RayTracer::UnitVector(ray.At(raycast) - Vector3{0, 0, -1});
            return 0.5 * Color{
                    raycastUnitDirection.X() + 1,
                    raycastUnitDirection.Y() + 1,
                    raycastUnitDirection.Z() + 1
            };
        }

        Vector3 unitDirection = RayTracer::UnitVector(ray.Direction());
        float alpha = 0.5f * (unitDirection.Y() + 1.0f);
        return (1 - alpha) * Color{1, 1, 1} + alpha * Color{0.5, 0.7, 1};
    }

}

#endif //RAYTRACER_RAYUTILITIES_H
