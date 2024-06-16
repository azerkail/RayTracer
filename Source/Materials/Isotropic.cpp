#include "Isotropic.h"

#include "Textures/SolidColorTexture.h"

namespace RayTracer
{
    Isotropic::Isotropic(const Color& albedo) : m_texture{std::make_shared<SolidColorTexture>(albedo)}
    {
    }

    Isotropic::Isotropic(std::shared_ptr<ITexture> texture) : m_texture{std::move(texture)}
    {
    }

    bool Isotropic::Scatter(const Ray& rayIn, const HitResult& result, Color& attenuation, Ray& scattered) const
    {
        scattered = Ray{result.Point, RandomInUnitVector(), rayIn.Time()};
        attenuation = m_texture->Value(result.U, result.V, result.Point);
        return true;
    }
}
