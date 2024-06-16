#ifndef ISOTROPIC_H
#define ISOTROPIC_H
#include "Textures/ITexture.h"

namespace RayTracer
{
    class Isotropic final : public IMaterial
    {
    public:
        explicit Isotropic(const Color& albedo);
        explicit Isotropic(std::shared_ptr<ITexture> texture);

        [[nodiscard]] bool Scatter(const Ray& rayIn, const HitResult& result, Color& attenuation,
                                   Ray& scattered) const override;

    private:
        std::shared_ptr<ITexture> m_texture;
    };
}

#endif
