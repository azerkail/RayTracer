#ifndef RAYTRACER_IMATERIAL_H
#define RAYTRACER_IMATERIAL_H

#include "RayTracerPCH.h"

namespace RayTracer {

    class IMaterial {
    public:
        virtual ~IMaterial() = default;

        [[nodiscard]] virtual bool Scatter(const Ray& rayIn, const HitResult& result, Color& attenuation,
                                           Ray& scattered) const = 0;
    };

}

#endif //RAYTRACER_IMATERIAL_H
