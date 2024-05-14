#ifndef RAYTRACER_SPHERE_H
#define RAYTRACER_SPHERE_H

#include "Hittable.h"

namespace RayTracer {

    class Sphere : public Hittable {
    public:
        Sphere(const Point3& center, float radius);

        bool Hit(const RayTracer::Ray& ray, float rayMin, float rayMax,
                 RayTracer::HitResult& result) const override;

    private:
        const Point3& m_center;
        float m_radius;
    };

}

#endif //RAYTRACER_SPHERE_H
