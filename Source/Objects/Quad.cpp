#include "Quad.h"

namespace RayTracer
{
    Quad::Quad(const Point3& q, const Vector3& u, const Vector3& v, std::shared_ptr<IMaterial> material)
        : m_q{q}, m_u{u}, m_v{v}, m_material(std::move(material))
    {
        const Vector3 normal = Cross(u, v);
        m_normal = UnitVector(normal);
        m_d = Dot(m_normal, m_q);
        m_w = normal / Dot(normal, normal);

        SetBoundingBox();
    }

    void Quad::SetBoundingBox()
    {
        const AABB boundingBoxDiagonal1{m_q, m_q + m_u + m_v};
        const AABB boundingBoxDiagonal2{m_q + m_u, m_q + m_v};
        m_boundingBox = {AABB{boundingBoxDiagonal1, boundingBoxDiagonal2}};
    }

    bool Quad::IsInterior(const float a, const float b, HitResult& result)
    {
        const Interval unitInterval{0, 1};

        if (!unitInterval.Contains(a) || !unitInterval.Contains(b))
        {
            return false;
        }

        result.U = a;
        result.V = b;
        return true;
    }

    bool Quad::Hit(const Ray& ray, const Interval interval, HitResult& result) const
    {
        const float denominator = Dot(m_normal, ray.Direction());

        // Ray is parallel to the plane.
        if (std::fabs(denominator) < 1e-8)
        {
            return false;
        }

        // Hit point is outside the ray interval.
        const float t = (m_d - Dot(m_normal, ray.Origin())) / denominator;
        if (!interval.Contains(t))
        {
            return false;
        }

        const Point3 intersection = ray.At(t);
        const Vector3 planarHitPointVector = intersection - m_q;
        const float alpha = Dot(m_w, Cross(planarHitPointVector, m_v));
        const float beta = Dot(m_w, Cross(m_u, planarHitPointVector));

        if (!IsInterior(alpha, beta, result))
        {
            return false;
        }

        result.Interval = t;
        result.Point = intersection;
        result.Material = m_material;
        result.SetFaceNormal(ray, m_normal);

        return true;
    }

    AABB Quad::BoundingBox() const
    {
        return m_boundingBox;
    }
}
