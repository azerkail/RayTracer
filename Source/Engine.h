#ifndef RAYTRACER_ENGINE_H
#define RAYTRACER_ENGINE_H

#include "Camera/Camera.h"

namespace RayTracer {

    class Engine {
    public:
        static void Trace();

    private:
        static HittableVector CreateWorld();
        static Camera CreateCamera();
    };

}

#endif //RAYTRACER_ENGINE_H
