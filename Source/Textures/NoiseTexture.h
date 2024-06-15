#ifndef NOISETEXTURE_H
#define NOISETEXTURE_H

#include "ITexture.h"
#include "Noise/Perlin.h"

namespace RayTracer
{
    class NoiseTexture final : public ITexture
    {
    public:
        NoiseTexture() = default;
        explicit NoiseTexture(float scale);

        [[nodiscard]] Color Value(float u, float v, const Point3& result) const override;

    private:
        Perlin m_noise;
        float m_scale;
    };
}

#endif // NOISETEXTURE_H
