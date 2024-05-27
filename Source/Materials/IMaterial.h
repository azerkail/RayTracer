#ifndef RAYTRACER_IMATERIAL_H
#define RAYTRACER_IMATERIAL_H

namespace RayTracer {

    // Prevents circular dependency with HitResult.
    class HitResult;

    class IMaterial {
    public:
        virtual ~IMaterial() = default;

        [[nodiscard]] virtual bool Scatter(const Ray& rayIn, const HitResult& result, Color& attenuation,
                                           Ray& scattered) const = 0;
    };

}

#endif // RAYTRACER_IMATERIAL_H
