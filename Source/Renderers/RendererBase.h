#ifndef RAYTRACER_RENDERERBASE_H
#define RAYTRACER_RENDERERBASE_H

#include "Maths/Vector3.h"

namespace RayTracer {

    class RendererBase {
    public:
        virtual void Initialise(float imageWidth, float imageHeight) = 0;
        virtual void Render(const Color& vector3) = 0;
        virtual void Terminate() const = 0;
    };

}

#endif //RAYTRACER_RENDERERBASE_H
