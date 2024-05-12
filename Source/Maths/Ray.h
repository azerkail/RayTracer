#ifndef RAYTRACER_RAY_H
#define RAYTRACER_RAY_H

#include "Vector3.h"

namespace RayTracer {

    class Ray {
    public:
        Ray();
        Ray(const Point3& origin, const Vector3& direction);

        const Point3& Origin() const;
        const Vector3& Direction() const;

        Point3 At(float value) const;
    private:
        Point3 m_origin;
        Vector3 m_direction;
    };

}

#endif //RAYTRACER_RAY_H
