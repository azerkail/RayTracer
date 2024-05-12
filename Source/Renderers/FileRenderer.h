#ifndef RAYTRACER_FILERENDERER_H
#define RAYTRACER_FILERENDERER_H

#include <ostream>
#include "Maths/Vector3.h"
#include "RendererBase.h"

namespace RayTracer {

    class FileRenderer : public RendererBase {
    public:
        void Initialise(int imageWidth, int imageHeight) override;
        void Render(const Color& pixel) override;
        void Terminate() const override;

    private:
        std::string m_image;
    };

}

#endif //RAYTRACER_FILERENDERER_H
