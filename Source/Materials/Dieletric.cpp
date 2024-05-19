#include "Dieletric.h"

namespace RayTracer {
    Dielectric::Dielectric(float refractionIndex) : m_refractionIndex(refractionIndex) {}

    bool Dielectric::Scatter(const Ray& rayIn, const HitResult& result, Color& attenuation, Ray& scattered) const {
        float refractionIndex = result.FrontFace ? (1.0f / m_refractionIndex) : m_refractionIndex;

        Vector3 unitDirection = UnitVector(rayIn.Direction());
        float costTheta = std::fmin(Dot(-unitDirection, result.Normal), 1.0f);
        float sinTheta = std::sqrt(1.0f - costTheta * costTheta);
        bool cannotRefract = refractionIndex * sinTheta > 1.0f;

        Vector3 direction;
        if (cannotRefract) {
            direction = Reflect(unitDirection, result.Normal);
        } else {
            direction = Refract(unitDirection, result.Normal, refractionIndex);
        }

        scattered = Ray{result.Point, direction};
        attenuation = {1.0f, 1.0f, 1.0f};

        return true;
    }
}
