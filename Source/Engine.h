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
        static HittableVector CreateQuads();
        static Camera CreateQuadsCamera();
        static HittableVector CreateSimpleLight();
        static Camera CreateSimpleLightCamera();
        static HittableVector CreateCornellBox();
        static Camera CreateCornellBoxCamera();
        static HittableVector CreateCornellSmoke();
        static Camera CreateCornellSmokeCamera();
        static HittableVector CreateFinalScene();
        static Camera CreateFinalSceneCamera(int imageWidth, int samplesPerPixel, int maxDepth);
    };
}

#endif
