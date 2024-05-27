#ifndef RAYTRACER_FILERENDERER_H
#define RAYTRACER_FILERENDERER_H

#include <ostream>
#include "IRenderer.h"

namespace RayTracer {

    class FileRenderer final : public IRenderer {
    public:
        void Initialise(int imageWidth, int imageHeight) override;
        void Render(const Color& pixel) override;
        void Terminate() const override;

    private:
        std::string m_image;
    };

}

#endif //RAYTRACER_FILERENDERER_H
