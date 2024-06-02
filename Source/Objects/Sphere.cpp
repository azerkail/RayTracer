#include <cmath>
#include <utility>
#include "Sphere.h"

namespace RayTracer
{
    Sphere::Sphere(const Point3& center, const float radius, std::shared_ptr<IMaterial> material)
        : m_center{center}, m_radius{std::fmax(0.0f, radius)}, m_material{std::move(material)}, m_isMoving(false)
    {
        const Vector3 radiusVector{radius, radius, radius};
        m_boundingBox = AABB{m_center - radiusVector, m_center + radiusVector};
    }

    Sphere::Sphere(const Point3& center1, const Point3& center2, const float radius,
                   std::shared_ptr<IMaterial> material) : m_center{center1}, m_radius{std::fmax(0.0f, radius)},
                                                          m_material{std::move(material)}, m_isMoving{true}
    {
        const Vector3 radiusVector{radius, radius, radius};
        const AABB boxAtStart{center1 - radiusVector, center1 + radiusVector};
        const AABB boxAtEnd{center2 - radiusVector, center2 + radiusVector};

        m_boundingBox = AABB{boxAtStart, boxAtEnd};
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
        GetSphereUV(outwardNormal, result.U, result.V);

        return true;
    }

    AABB Sphere::BoundingBox() const
    {
        return m_boundingBox;
    }

    void Sphere::GetSphereUV(const Point3& point, float& u, float& v)
    {
        // p: a given point on the sphere of radius one, centered at the origin.
        // u: returned value [0,1] of angle around the Y axis from X=-1.
        // v: returned value [0,1] of angle from Y=-1 to Y=+1.
        //     <1 0 0> yields <0.50 0.50>       <-1  0  0> yields <0.00 0.50>
        //     <0 1 0> yields <0.50 1.00>       < 0 -1  0> yields <0.50 0.00>
        //     <0 0 1> yields <0.25 0.50>       < 0  0 -1> yields <0.75 0.50>

        const float theta = std::acos(-point.Y());
        const float phi = std::atan2(-point.Z(), point.X()) + Constants::Pi;

        u = phi / (2 * Constants::Pi);
        v = theta / Constants::Pi;
    }

    Point3 Sphere::SphereCenter(const float time) const
    {
        return m_center + time * m_centerVector;
    }
}
