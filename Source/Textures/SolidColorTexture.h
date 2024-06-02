#ifndef SOLIDCOLORTEXTURE_H
#define SOLIDCOLORTEXTURE_H

#include "ITexture.h"

namespace RayTracer
{
    class SolidColorTexture final : public ITexture
    {
    public:
        explicit SolidColorTexture(const Color& albedo);
        SolidColorTexture(float red, float green, float blue);

        [[nodiscard]] Color Value(float u, float v, const Point3& result) const override;

    private:
        Color m_albedo;
    };
}

#endif // SOLIDCOLORTEXTURE_H
