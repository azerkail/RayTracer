#include "Metal.h"

namespace RayTracer
{
    Metal::Metal(const Color& albedo, const float fuzz) : m_albedo(albedo), m_fuzz(fuzz < 1 ? fuzz : 1)
    {
    }

    bool Metal::Scatter(const Ray& rayIn, const HitResult& result, Color& attenuation, Ray& scattered) const
    {
        Vector3 reflected = Reflect(rayIn.Direction(), result.Normal);
        reflected = UnitVector(reflected) + (m_fuzz * RandomInUnitVector());

        scattered = Ray{result.Point, reflected, rayIn.Time()};
        attenuation = m_albedo;

        return Dot(scattered.Direction(), result.Normal) > 0;
    }
}
