#ifndef RAYTRACER_HITRESULT_H
#define RAYTRACER_HITRESULT_H

#include "Materials/IMaterial.h"

namespace RayTracer
{
    // Prevents circular dependency with IMaterial.
    class IMaterial;

    class HitResult
    {
    public:
        Point3 Point;
        Vector3 Normal;
        float Interval = 0;
        float U = 0;
        float V = 0;
        bool FrontFace = false;
        std::shared_ptr<IMaterial> Material;

        void SetFaceNormal(const Ray& ray, const Vector3& outwardNormal);
    };
}

#endif //RAYTRACER_HITRESULT_H
