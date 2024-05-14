#include "HittableVector.h"

namespace RayTracer {
    HittableVector::HittableVector(const std::shared_ptr<Hittable>& object) {
        Add(object);
    }

    void HittableVector::Clear() {
        m_objects.clear();
    }

    void HittableVector::Add(const std::shared_ptr<Hittable>& object) {
        m_objects.push_back(object);
    }

    bool HittableVector::Hit(const Ray& ray, float rayMin, float rayMax, HitResult& result) const {
        HitResult temporaryResult;
        bool hitAnything = false;
        auto closesSoFar = rayMax;

        for (const auto& object: m_objects) {
            if (object->Hit(ray, rayMin, closesSoFar, temporaryResult)) {
                hitAnything = true;
                closesSoFar = temporaryResult.Interval;
                result = temporaryResult;
            }
        }

        return hitAnything;
    }
}
