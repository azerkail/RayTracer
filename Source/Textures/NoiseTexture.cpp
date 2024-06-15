#include "NoiseTexture.h"

namespace RayTracer
{
    NoiseTexture::NoiseTexture(const float scale) : m_scale{scale}
    {
    }

    Color NoiseTexture::Value([[maybe_unused]] float u, [[maybe_unused]] float v, const Point3& result) const
    {
        return Color{.5, .5, .5} * (1 + std::sin(m_scale * result.Z() + 10 * m_noise.Turbulance(result, 7)));
    }
}
