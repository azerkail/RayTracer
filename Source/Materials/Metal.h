#ifndef RAYTRACER_METAL_H
#define RAYTRACER_METAL_H

#include "IMaterial.h"

namespace RayTracer {

    class Metal : public IMaterial {
    public:
        explicit Metal(const Color& albedo);

        [[nodiscard]] bool Scatter(const Ray& rayIn, const HitResult& result, Color& attenuation,
                                   Ray& scattered) const override;
    private:
        Color m_albedo;
    };

}

#endif //RAYTRACER_METAL_H
