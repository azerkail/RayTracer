#include "NoiseTexture.h"

namespace RayTracer
{
    NoiseTexture::NoiseTexture(const float scale) : m_scale{scale}
    {
    }

    Color NoiseTexture::Value([[maybe_unused]] float u, [[maybe_unused]] float v, const Point3& result) const
    {
        return Color{1, 1, 1} * m_noise.Noise(m_scale * result);
    }
}
