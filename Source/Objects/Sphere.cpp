#include <cmath>
#include <utility>
#include "Sphere.h"

namespace RayTracer
{
    Sphere::Sphere(const Point3& center, const float radius, std::shared_ptr<IMaterial> material)
        : m_center{center}, m_radius{std::fmax(0.0f, radius)}, m_material{std::move(material)}, m_isMoving(false)
    {
    }

    Sphere::Sphere(const Point3& center1, const Point3 center2, const float radius,
                   std::shared_ptr<IMaterial> material) : m_center{center1}, m_radius{std::fmax(0.0f, radius)},
                                                          m_material{std::move(material)}, m_isMoving{true}
    {
        m_centerVector = center2 - m_center;
    }

    bool Sphere::Hit(const Ray& ray, const Interval interval, HitResult& result) const
    {
        const Point3 center = m_isMoving ? SphereCenter(ray.Time()) : m_center;
        const Vector3 origin = center - ray.Origin();
        const float a = ray.Direction().LengthSquared();
        const float h = Dot(ray.Direction(), origin);
        const float c = origin.LengthSquared() - m_radius * m_radius;
        const float discriminant = h * h - a * c;

        if (discriminant < 0)
        {
            return false;
        }

        const auto sqrtd = std::sqrt(discriminant);
        auto root = (h - sqrtd) / a;

        if (!interval.Surrounds(root))
        {
            root = (h + sqrtd) / a;

            if (!interval.Surrounds(root))
            {
                return false;
            }
        }

        result.Interval = root;
        result.Point = ray.At(result.Interval);
        result.Material = m_material;

        const Vector3 outwardNormal = (result.Point - m_center) / m_radius;
        result.SetFaceNormal(ray, outwardNormal);

        return true;
    }

    Point3 Sphere::SphereCenter(const double time) const
    {
        return m_center + time * m_centerVector;
    }
}
