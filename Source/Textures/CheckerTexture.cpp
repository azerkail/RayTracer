#include "CheckerTexture.h"

#include <utility>

#include "SolidColorTexture.h"

namespace RayTracer
{
    CheckerTexture::CheckerTexture(const float scale, std::shared_ptr<ITexture> even,
                                   std::shared_ptr<ITexture> odd) : m_scaleFactor{1.0f / scale},
                                                                    m_even{std::move(even)},
                                                                    m_odd{std::move(odd)}
    {
    }

    CheckerTexture::CheckerTexture(const float scale, const Color& evenColor, const Color& oddColor)
        : m_scaleFactor{1.0f / scale},
          m_even{std::make_shared<SolidColorTexture>(evenColor)},
          m_odd{std::make_shared<SolidColorTexture>(oddColor)}
    {
    }

    Color CheckerTexture::Value(const float u, const float v, const Point3& point) const
    {
        const int xInteger = static_cast<int>(std::floor(m_scaleFactor * point.X()));
        const int yInteger = static_cast<int>(std::floor(m_scaleFactor * point.Y()));
        const int zInteger = static_cast<int>(std::floor(m_scaleFactor * point.Z()));
        const bool isEven = (xInteger + yInteger + zInteger) % 2 == 0;

        return isEven ? m_even->Value(u, v, point) : m_odd->Value(u, v, point);
    }
}
