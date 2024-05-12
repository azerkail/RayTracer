#ifndef RAYTRACER_ENGINE_H
#define RAYTRACER_ENGINE_H

#include "Renderers/RendererBase.h"

namespace RayTracer {

    class Engine {
    public:
        explicit Engine(RendererBase& renderer);

        void Trace();
        void Terminate();
    private:
        inline static const int m_baseImageWidth = 256;
        inline static const int m_baseImageHeight = 256;

        RendererBase& m_renderer;
    };

}

#endif //RAYTRACER_ENGINE_H
