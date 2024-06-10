#include "NoiseTexture.h"

namespace RayTracer
{
    Color NoiseTexture::Value([[maybe_unused]] float u, [[maybe_unused]] float v, const Point3& result) const
    {
        return Color{1, 1, 1} * m_noise.Noise(result);
    }
}
