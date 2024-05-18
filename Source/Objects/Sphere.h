#ifndef RAYTRACER_SPHERE_H
#define RAYTRACER_SPHERE_H

#include "Hittable.h"

namespace RayTracer {

    class Sphere : public Hittable {
    public:
        Sphere(const Point3& center, float radius);

        bool Hit(const RayTracer::Ray& ray, Interval interval, RayTracer::HitResult& result) const override;

    private:
        const Point3 m_center;
        const float m_radius;
        std::shared_ptr<IMaterial> m_material;
    };

}

#endif //RAYTRACER_SPHERE_H
