#ifndef RAYTRACER_HITRESULT_H
#define RAYTRACER_HITRESULT_H

#include "Maths/Vector3.h"
#include "Maths/Ray.h"

namespace RayTracer {

    class HitResult {
    public:
        Point3 Point;
        Vector3 Normal;
        float Interval = 0;
        bool FrontFace = false;

        void SetFaceNormal(const Ray& ray, const Vector3& outwardNormal);
    };

}

#endif //RAYTRACER_HITRESULT_H
