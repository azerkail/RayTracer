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

    bool HittableVector::Hit(const Ray& ray, const Interval interval, HitResult& result) const {
        HitResult temporaryResult;
        bool hitAnything = false;
        auto closesSoFar = interval.GetMax();

        for (const auto& object: m_objects) {
            if (object->Hit(ray, Interval{interval.GetMin(), closesSoFar}, temporaryResult)) {
                hitAnything = true;
                closesSoFar = temporaryResult.Interval;
                result = temporaryResult;
            }
        }

        return hitAnything;
    }
}
