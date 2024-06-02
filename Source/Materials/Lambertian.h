#ifndef RAYTRACER_LAMBERTIAN_H
#define RAYTRACER_LAMBERTIAN_H

#include "IMaterial.h"
#include "Textures/ITexture.h"

namespace RayTracer
{
    class Lambertian final : public IMaterial
    {
    public:
        explicit Lambertian(const Color& albedo);
        explicit Lambertian(std::shared_ptr<ITexture> texture);

        [[nodiscard]] bool Scatter(const Ray& rayIn, const HitResult& result, Color& attenuation,
                                   Ray& scattered) const override;

    private:
        std::shared_ptr<ITexture> m_texture;
    };
}

#endif //RAYTRACER_LAMBERTIAN_H
