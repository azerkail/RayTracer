#ifndef RAYTRACER_HITTABLEVECTOR_H
#define RAYTRACER_HITTABLEVECTOR_H

#include <vector>
#include <memory>
#include "Objects/Hittable.h"

namespace RayTracer
{
    class HittableVector
    {
    public:
        HittableVector() = default;
        explicit HittableVector(const std::shared_ptr<Hittable>& object);

        void Clear();
        void Add(const std::shared_ptr<Hittable>& object);

        bool Hit(const Ray& ray, Interval interval, HitResult& result) const;

        [[nodiscard]] std::vector<std::shared_ptr<Hittable>>& GetObjects();
        [[nodiscard]] AABB BoundingBox() const;

    private:
        std::vector<std::shared_ptr<Hittable>> m_objects;
        AABB m_boundingBox;
    };
}

#endif //RAYTRACER_HITTABLEVECTOR_H
