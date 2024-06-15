#ifndef RAYTRACER_HITTABLEVECTOR_H
#define RAYTRACER_HITTABLEVECTOR_H

#include <vector>
#include <memory>
#include "Objects/IHittable.h"

namespace RayTracer
{
    class HittableVector
    {
    public:
        HittableVector() = default;
        explicit HittableVector(const std::shared_ptr<IHittable>& object);

        void Clear();
        void Add(const std::shared_ptr<IHittable>& object);
        void Add(const HittableVector& other);

        bool Hit(const Ray& ray, Interval interval, HitResult& result) const;

        [[nodiscard]] std::vector<std::shared_ptr<IHittable>>& GetObjects();
        [[nodiscard]] AABB BoundingBox() const;

    private:
        std::vector<std::shared_ptr<IHittable>> m_objects;
        AABB m_boundingBox;
    };
}

#endif //RAYTRACER_HITTABLEVECTOR_H
