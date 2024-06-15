#include "Translate.h"

namespace RayTracer
{
    Translate::Translate(std::shared_ptr<IHittable> object, const Vector3& offset) : m_object{std::move(object)},
        m_offset{offset}
    {
        m_boundingBox = object->BoundingBox() + offset;
    }

    bool Translate::Hit(const Ray& ray, const Interval interval, HitResult& result) const
    {
        const Ray offsetRay{ray.Origin() - m_offset, ray.Direction(), ray.Time()};

        if (!m_object->Hit(offsetRay, interval, result))
        {
            return false;
        }

        result.Point += m_offset;

        return true;
    }

    AABB Translate::BoundingBox() const
    {
        return m_boundingBox;
    }
}
