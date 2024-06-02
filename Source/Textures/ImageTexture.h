#ifndef IMAGETEXTURE_H
#define IMAGETEXTURE_H

#include "ITexture.h"
#include "External/RTWImage.h"

namespace RayTracer
{
    class ImageTexture final : public ITexture
    {
    public:
        explicit ImageTexture(const char* filename);

        [[nodiscard]] Color Value(float u, float v, const Point3& result) const override;

    private:
        RTWImage m_image;
    };
}

#endif
