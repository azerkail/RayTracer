#ifndef CONSTANTMEDIUM_H
#define CONSTANTMEDIUM_H
#include "Textures/ITexture.h"

namespace RayTracer
{
    class ConstantMedium final : public IHittable
    {
    public:
        ConstantMedium(std::shared_ptr<IHittable> boundary, float density, std::shared_ptr<ITexture> texture);
        ConstantMedium(std::shared_ptr<IHittable> boundary, float density, const Color& albedo);

        bool Hit(const Ray& ray, Interval interval, HitResult& result) const override;
        [[nodiscard]] AABB BoundingBox() const override;

    private:
        std::shared_ptr<IHittable> m_boundary;
        float m_negativeInvisibleDensity;
        std::shared_ptr<IMaterial> m_phaseFunction;
    };
}

#endif
