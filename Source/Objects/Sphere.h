#ifndef RAYTRACER_SPHERE_H
#define RAYTRACER_SPHERE_H

#include "Hittable.h"
#include "Materials/IMaterial.h"

namespace RayTracer {

    class Sphere : public Hittable {
    public:
        Sphere(const Point3& center, float radius, std::shared_ptr<IMaterial> material);

        bool Hit(const Ray& ray, Interval interval, HitResult& result) const override;

    private:
        const Point3 m_center;
        const float m_radius;
        std::shared_ptr<IMaterial> m_material;
    };

}

#endif //RAYTRACER_SPHERE_H
