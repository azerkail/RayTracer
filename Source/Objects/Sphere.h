#ifndef RAYTRACER_SPHERE_H
#define RAYTRACER_SPHERE_H

#include "Hittable.h"
#include "Materials/IMaterial.h"

namespace RayTracer
{
    class Sphere final : public Hittable
    {
    public:
        Sphere(const Point3& center, float radius, std::shared_ptr<IMaterial> material);
        Sphere(const Point3& center1, const Point3& center2, float radius, std::shared_ptr<IMaterial> material);

        bool Hit(const Ray& ray, Interval interval, HitResult& result) const override;
        [[nodiscard]] AABB BoundingBox() const override;

    private:
        const Point3 m_center;
        const float m_radius;
        std::shared_ptr<IMaterial> m_material;
        bool m_isMoving;
        Vector3 m_centerVector;
        AABB m_boundingBox;

        [[nodiscard]] Point3 SphereCenter(float time) const;
    };
}

#endif //RAYTRACER_SPHERE_H
