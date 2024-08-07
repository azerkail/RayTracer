#ifndef RAYTRACER_RAY_H
#define RAYTRACER_RAY_H

#include "Vector3.h"

namespace RayTracer {

    class Ray {
    public:
        Ray();
        Ray(const Point3& origin, const Vector3& direction);
        Ray(const Point3& origin, const Vector3& direction, float time);

        [[nodiscard]] const Point3& Origin() const;
        [[nodiscard]] const Vector3& Direction() const;
        [[nodiscard]] float Time() const;

        [[nodiscard]] Point3 At(float value) const;
    private:
        Point3 m_origin;
        Vector3 m_direction;
        float m_time = 0.0f;
    };

}

#endif //RAYTRACER_RAY_H
