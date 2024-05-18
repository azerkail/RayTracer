#include "Lambertian.h"

namespace RayTracer {
    Lambertian::Lambertian(const Color& albedo) : m_albedo(albedo) {}

    bool Lambertian::Scatter(const Ray& rayIn, const HitResult& result, Color& attenuation, Ray& scattered) const {
        auto scatterDirection = result.Normal + RandomUnitVector();

        if (scatterDirection.NearZero()) {
            scatterDirection = result.Normal;
        }

        scattered = Ray{result.Point, scatterDirection};
        attenuation = m_albedo;

        return true;
    }
}
