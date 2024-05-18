#ifndef RAYTRACER_LAMBERTIAN_H
#define RAYTRACER_LAMBERTIAN_H

#include "IMaterial.h"

namespace RayTracer {

    class Lambertian : public IMaterial {
    public:
        explicit Lambertian(const Color& albedo);

        [[nodiscard]] bool Scatter(const Ray& rayIn, const HitResult& result, Color& attenuation,
                                   Ray& scattered) const override;

    private:
        Color m_albedo;
    };

}

#endif //RAYTRACER_LAMBERTIAN_H
