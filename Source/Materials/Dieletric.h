#ifndef RAYTRACER_DIELETRIC_H
#define RAYTRACER_DIELETRIC_H

namespace RayTracer {

    class Dielectric final : public IMaterial {
    public:
        explicit Dielectric(float refractionIndex);

        [[nodiscard]] bool Scatter(const Ray& rayIn, const HitResult& result, Color& attenuation,
                                   Ray& scattered) const override;
    private:
        float m_refractionIndex;

        static float Reflectance(float cosine, float refractionIndex);
    };

}

#endif //RAYTRACER_DIELETRIC_H
