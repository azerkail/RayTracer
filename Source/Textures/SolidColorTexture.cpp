#include "SolidColorTexture.h"

namespace RayTracer
{
    SolidColorTexture::SolidColorTexture(const Color& albedo) : m_albedo{albedo}
    {
    }

    SolidColorTexture::SolidColorTexture(const float red, const float green, const float blue) : SolidColorTexture(
        Color{red, green, blue})
    {
    }

    Color SolidColorTexture::Value([[maybe_unused]] const float u, [[maybe_unused]] const float v,
                                   [[maybe_unused]] const Point3& result) const
    {
        return m_albedo;
    }
}
