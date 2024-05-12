#ifndef RAYTRACER_RAYTRACER_H
#define RAYTRACER_RAYTRACER_H

#include "Renderers/RendererBase.h"

namespace RayTracer {

    class RayTracer {
    public:
        explicit RayTracer(const RendererBase& renderer);

        void Trace();
        void Finish();
    private:
        inline static const int m_baseImageWidth = 256;
        inline static const int m_baseImageHeight = 256;

        const RendererBase& m_renderer;
        std::string m_image;
    };

}

#endif //RAYTRACER_RAYTRACER_H
