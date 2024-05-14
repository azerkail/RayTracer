#include "HitResult.h"

namespace RayTracer {
    void HitResult::SetFaceNormal(const Ray& ray, const Vector3& outwardNormal) {
        // Outward normal is assumed unit vector.
        FrontFace = Dot(ray.Direction(), outwardNormal) < 0;
        Normal = FrontFace ? outwardNormal : -outwardNormal;
    }
}
