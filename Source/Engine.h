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
        static HittableVector CreateEarth();
        static Camera CreateEarthCamera();
        static HittableVector CreatePerlinSpheres();
        static Camera CreatePerlinSpheresCamera();
    };
}

#endif
