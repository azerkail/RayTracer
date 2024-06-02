#include "Lambertian.h"
#include "Textures/SolidColorTexture.h"

namespace RayTracer
{
    Lambertian::Lambertian(const Color& albedo) : m_texture{std::make_shared<SolidColorTexture>(albedo)}
    {
    }

    Lambertian::Lambertian(std::shared_ptr<ITexture> texture) : m_texture{std::move(texture)}
    {
    }

    bool Lambertian::Scatter(const Ray& rayIn, const HitResult& result, Color& attenuation, Ray& scattered) const
    {
        // Stops compiler warning about unused parameter as we do not need "rayIn" when scattering lambertian materials.
        (void)rayIn;
        auto scatterDirection = result.Normal + RandomInUnitVector();

        if (scatterDirection.NearZero())
        {
            scatterDirection = result.Normal;
        }

        scattered = Ray{result.Point, scatterDirection, rayIn.Time()};
        attenuation = m_texture->Value(result.U, result.V, result.Point);

        return true;
    }
}
