#include "Metal.h"

namespace RayTracer {
    Metal::Metal(const Color& albedo) : m_albedo(albedo) {}

    bool Metal::Scatter(const Ray& rayIn, const HitResult& result, Color& attenuation, Ray& scattered) const {
        Vector3 reflected = Reflect(rayIn.Direction(), result.Normal);

        scattered = Ray{result.Point, reflected};
        attenuation = m_albedo;

        return true;
    }


}
