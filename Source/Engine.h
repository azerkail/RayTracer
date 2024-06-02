#ifndef RAYTRACER_ENGINE_H
#define RAYTRACER_ENGINE_H

#include "Camera/Camera.h"

namespace RayTracer
{
    class Engine
    {
    public:
        static void Trace();

    private:
        static HittableVector CreateBouncingSpheres();
        static Camera CreateBouncingSpheresCamera();
        static HittableVector CreateCheckeredSpheres();
        static Camera CreateCheckeredSpheresCamera();
    };
}

#endif //RAYTRACER_ENGINE_H
