#include "DiffuseLight.h"
#include "Textures/SolidColorTexture.h"

namespace RayTracer
{
    DiffuseLight::DiffuseLight(std::shared_ptr<ITexture> texture) : m_texture{std::move(texture)}
    {
    }

    DiffuseLight::DiffuseLight(const Color& emit) : m_texture{std::make_shared<SolidColorTexture>(emit)}
    {
    }

    Color DiffuseLight::Emit(const float u, const float v, const Point3& point) const
    {
        return m_texture->Value(u, v, point);
    }
}
