#ifndef RAYTRACER_METAL_H
#define RAYTRACER_METAL_H

#include "IMaterial.h"

namespace RayTracer {

    class Metal final : public IMaterial {
    public:
        explicit Metal(const Color& albedo, float fuzz);

        [[nodiscard]] bool Scatter(const Ray& rayIn, const HitResult& result, Color& attenuation,
                                   Ray& scattered) const override;
    private:
        Color m_albedo;
        float m_fuzz;
    };

}

#endif //RAYTRACER_METAL_H
