#ifndef RAYTRACER_IMATERIAL_H
#define RAYTRACER_IMATERIAL_H

namespace RayTracer
{
    // Prevents circular dependency with HitResult.
    class HitResult;

    class IMaterial
    {
    public:
        virtual ~IMaterial() = default;

        [[nodiscard]] virtual bool Scatter(const Ray& rayIn, const HitResult& result, Color& attenuation,
                                           Ray& scattered) const { return false; };
        [[nodiscard]] virtual Color Emit(float u, float v, const Point3& point) const { return Color{0, 0, 0}; };
    };
}

#endif // RAYTRACER_IMATERIAL_H
