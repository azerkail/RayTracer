#ifndef RAYTRACER_ENGINE_H
#define RAYTRACER_ENGINE_H

#include "Renderers/RendererBase.h"

namespace RayTracer {

    class Engine {
    public:
        explicit Engine(const RendererBase& renderer);

        void Trace();
        void Finish();
    private:
        inline static const int m_baseImageWidth = 256;
        inline static const int m_baseImageHeight = 256;

        const RendererBase& m_renderer;
        std::string m_image;
    };

}

#endif //RAYTRACER_ENGINE_H
