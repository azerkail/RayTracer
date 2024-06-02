#include "ImageTexture.h"

namespace RayTracer
{
    ImageTexture::ImageTexture(const char* filename) : m_image{filename}
    {
    }

    Color ImageTexture::Value(float u, float v, [[maybe_unused]] const Point3& result) const
    {
        // Returns cyan as a debugging aid if we have no texture data.
        if (m_image.Height() <= 0)
        {
            return Color{0, 1, 1};
        }

        u = Interval{0, 1}.Clamp(u);
        v = 1.0f - Interval{0, 1}.Clamp(v);

        const int i = static_cast<int>(u) * m_image.Width();
        const int j = static_cast<int>(v) * m_image.Height();
        constexpr float colorScale = 1.0f / 255.0f;
        const unsigned char* pixel = m_image.PixelData(i, j);
        const auto pixelX = static_cast<float>(pixel[0]);
        const auto pixelY = static_cast<float>(pixel[1]);
        const auto pixelZ = static_cast<float>(pixel[2]);

        return Color{colorScale * pixelX, colorScale * pixelY, colorScale * pixelZ};
    }
}
