#ifndef RAYTRACER_RENDERERBASE_H
#define RAYTRACER_RENDERERBASE_H

#include "Maths/Vector3.h"

namespace RayTracer {

    class RendererBase {
    public:
        [[nodiscard]] virtual std::string Render(const Color& vector3) const = 0;
    };

}

#endif //RAYTRACER_RENDERERBASE_H
