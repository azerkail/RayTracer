#ifndef RAYTRACER_RAYUTILITIES_H
#define RAYTRACER_RAYUTILITIES_H

#include "Vector3.h"
#include "Ray.h"

namespace RayTracer {

    inline bool HitSphere(const Point3& center, float radius, const Ray& ray) {
        Vector3 origin = center - ray.Origin();
        float a = RayTracer::Dot(ray.Direction(), ray.Direction());
        float b = -2.0f * RayTracer::Dot(ray.Direction(), origin);
        float c = RayTracer::Dot(origin, origin) - radius * radius;
        float discriminant = b * b - 4 * a * c;
        return discriminant >= 0;
    }

    inline Color GetRayColor(const Ray& ray) {
        if (RayTracer::HitSphere(Point3{0, 0, -1}, 0.5, ray)) {
            return Color{1, 0, 0};
        }

        Vector3 unitDirection = RayTracer::UnitVector(ray.Direction());
        float alpha = 0.5f * (unitDirection.Y() + 1.0f);
        return (1 - alpha) * Color{1, 1, 1} + alpha * Color{0.5, 0.7, 1};
    }

}

#endif //RAYTRACER_RAYUTILITIES_H
