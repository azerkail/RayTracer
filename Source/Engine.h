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
        int m_imageWidth;
        int m_imageHeight;
        Camera m_camera;
        std::unique_ptr<RendererBase> m_renderer;
    };

}

#endif //RAYTRACER_ENGINE_H
