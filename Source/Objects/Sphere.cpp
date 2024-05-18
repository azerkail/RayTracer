#include <cmath>
#include "Sphere.h"

namespace RayTracer {
    Sphere::Sphere(const Point3& center, float radius) : m_center{center}, m_radius{std::fmax(0.0f, radius)} {}

    bool Sphere::Hit(const Ray& ray, Interval interval, HitResult& result) const {
        Vector3 origin = m_center - ray.Origin();
        float a = ray.Direction().LengthSquared();
        float h = Dot(ray.Direction(), origin);
        float c = origin.LengthSquared() - m_radius * m_radius;
        float discriminant = h * h - a * c;

        if (discriminant < 0) {
            return false;
        }

        auto sqrtd = std::sqrt(discriminant);
        auto root = (h - sqrtd) / a;

        if (!interval.Surrounds(root)) {
            root = (h + sqrtd) / a;

            if (!interval.Surrounds(root)) {
                return false;
            }
        }

        result.Interval = root;
        result.Point = ray.At(result.Interval);
        result.Material = m_material;

        Vector3 outwardNormal = (result.Point - m_center) / m_radius;
        result.SetFaceNormal(ray, outwardNormal);

        return true;
    }
}
