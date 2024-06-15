#ifndef RAYTRACER_HITTABLEVECTOR_H
#define RAYTRACER_HITTABLEVECTOR_H

#include <vector>
#include <memory>
#include "Objects/IHittable.h"

namespace RayTracer
{
    class HittableVector final : public IHittable
    {
    public:
        HittableVector() = default;
        explicit HittableVector(const std::shared_ptr<IHittable>& object);

        void Clear();
        void Add(const std::shared_ptr<IHittable>& object);
        [[nodiscard]] std::vector<std::shared_ptr<IHittable>>& GetObjects();

        bool Hit(const Ray& ray, Interval interval, HitResult& result) const override;
        [[nodiscard]] AABB BoundingBox() const override;

    private:
        std::vector<std::shared_ptr<IHittable>> m_objects;
        AABB m_boundingBox;
    };
}

#endif //RAYTRACER_HITTABLEVECTOR_H
