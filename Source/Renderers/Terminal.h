#ifndef RAYTRACER_TERMINAL_H
#define RAYTRACER_TERMINAL_H

#include <ostream>
#include "Maths/Vector3.h"
#include "RendererBase.h"

namespace RayTracer {

    class Terminal : public RendererBase {
    public:
        std::string Render(const Color& pixel) const override;
    };

}

#endif //RAYTRACER_TERMINAL_H
