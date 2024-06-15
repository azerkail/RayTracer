#ifndef DIFFUSELIGHT_H
#define DIFFUSELIGHT_H

#include "Textures/ITexture.h"

namespace RayTracer
{
    class DiffuseLight final : public IMaterial
    {
    public:
        explicit DiffuseLight(std::shared_ptr<ITexture> texture);
        explicit DiffuseLight(const Color& emit);

        [[nodiscard]] Color Emit(float u, float v, const Point3& point) const override;

    private:
        std::shared_ptr<ITexture> m_texture;
    };
}

#endif
