#ifndef RAYTRACER_FILERENDERER_H
#define RAYTRACER_FILERENDERER_H

#include <ostream>
#include "Maths/Vector3.h"
#include "RendererBase.h"

namespace RayTracer {

    class FileRenderer : public RendererBase {
    public:
        FileRenderer(const Camera& camera, int imageWidth, int imageHeight);

        void Render(const Color& pixel) override;
        void Terminate() const override;

    private:
        const Camera& m_camera;
        std::string m_image;
    };

}

#endif //RAYTRACER_FILERENDERER_H
