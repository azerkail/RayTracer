#include "Ray.h"

namespace RayTracer
{
    Ray::Ray() = default;

    Ray::Ray(const Point3& origin, const Vector3& direction) : m_origin{origin}, m_direction{direction}
    {
    }

    Ray::Ray(const Point3& origin, const Vector3& direction, const float time) : m_origin{origin},
        m_direction{direction}, m_time{time}
    {
    }

    const Point3& Ray::Origin() const
    {
        return m_origin;
    }

    const Vector3& Ray::Direction() const
    {
        return m_direction;
    }

    Point3 Ray::At(const float value) const
    {
        return m_origin + value * m_direction;
    }

    float Ray::Time() const
    {
        return m_time;
    }
}
