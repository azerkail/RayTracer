#ifndef RAYTRACER_ENGINE_H
#define RAYTRACER_ENGINE_H

#include <bits/unique_ptr.h>
#include "Renderers/RendererBase.h"

namespace RayTracer {

    class Engine {
    public:
        void Initialise();
        void Trace();
        void Terminate();
    private:
        inline static const int m_baseImageWidth = 256;
        inline static const int m_baseImageHeight = 256;

        Camera m_camera;
        std::unique_ptr<RendererBase> m_renderer;
    };

}

#endif //RAYTRACER_ENGINE_H
