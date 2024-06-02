#ifndef CHECKERTEXTURE_H
#define CHECKERTEXTURE_H

#include "ITexture.h"

namespace RayTracer
{
    class CheckerTexture final : public ITexture
    {
    public:
        CheckerTexture(float scale, std::shared_ptr<ITexture> even, std::shared_ptr<ITexture> odd);
        CheckerTexture(float scale, const Color& evenColor, const Color& oddColor);

        [[nodiscard]] Color Value(float u, float v, const Point3& point) const override;

    private:
        float m_scaleFactor;
        std::shared_ptr<ITexture> m_even;
        std::shared_ptr<ITexture> m_odd;
    };
}

#endif // CHECKERTEXTURE_H
