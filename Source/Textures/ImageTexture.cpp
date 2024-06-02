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

        const int i = u * m_image.Width(); // NOLINT(*-narrowing-conversions)
        const int j = v * m_image.Height(); // NOLINT(*-narrowing-conversions)
        constexpr float colorScale = 1.0f / 255.0f;
        const unsigned char* pixel = m_image.PixelData(i, j);

        return Color{colorScale * pixel[0], colorScale * pixel[1], colorScale * pixel[2]}; // NOLINT(*-narrowing-conversions)
    }
}
