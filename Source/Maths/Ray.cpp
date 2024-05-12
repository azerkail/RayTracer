#include "Ray.h"

namespace RayTracer {
    Ray::Ray() : m_origin{}, m_direction{} {

    }

    Ray::Ray(const Point3& origin, const Vector3& direction) : m_origin(origin), m_direction(direction) {

    }

    const Point3& Ray::Origin() const {
        return m_origin;
    }

    const Vector3& Ray::Direction() const {
        return m_direction;
    }

    Point3 Ray::At(float value) const {
        return m_origin + value * m_direction;
    }

    Color GetRayColor(const Ray& ray) {
        return Color{0, 0, 0};
    }
}
