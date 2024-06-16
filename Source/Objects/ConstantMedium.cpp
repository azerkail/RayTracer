#include "ConstantMedium.h"

#include "Materials/Isotropic.h"

namespace RayTracer
{
    ConstantMedium::ConstantMedium(std::shared_ptr<IHittable> boundary, const float density,
                                   std::shared_ptr<ITexture> texture) :
        m_boundary{std::move(boundary)},
        m_negativeInvisibleDensity{-1 / density},
        m_phaseFunction{std::make_shared<Isotropic>(std::move(texture))}
    {
    }

    ConstantMedium::ConstantMedium(std::shared_ptr<IHittable> boundary, const float density, const Color& albedo) :
        m_boundary{std::move(boundary)}, m_negativeInvisibleDensity{-1 / density},
        m_phaseFunction{std::make_shared<Isotropic>(albedo)}
    {
    }

    bool ConstantMedium::Hit(const Ray& ray, const Interval interval, HitResult& result) const
    {
        constexpr bool enableDebug = false;
        constexpr bool debugging = enableDebug && Utilities::RandomFloat() < 0.00001f;

        HitResult result1, result2;

        if (!m_boundary->Hit(ray, Constants::IntervalUniverse, result1))
        {
            return false;
        }

        if (!m_boundary->Hit(ray, Interval{result1.Interval + 0.0001f, Constants::Infinity}, result2))
        {
            return false;
        }

        if (debugging)
        {
            LOG_INFO("IntervalMin = {0}, IntervalMax = {1}", result1.Interval, result2.Interval);
        }

        if (result1.Interval < interval.Min())
        {
            result1.Interval = interval.Min();
        }

        if (result2.Interval > interval.Max())
        {
            result2.Interval = interval.Max();
        }

        if (result1.Interval >= result2.Interval)
        {
            return false;
        }

        if (result1.Interval < 0)
        {
            result1.Interval = 0;
        }

        const float rayLength = ray.Direction().Length();
        const float distanceInsideBoundary = (result2.Interval - result1.Interval) * rayLength;
        const float hitDistance = m_negativeInvisibleDensity * std::log(Utilities::RandomFloat());

        if (hitDistance > distanceInsideBoundary)
        {
            return false;
        }

        result.Interval = result1.Interval + hitDistance / rayLength;
        result.Point = ray.At(result.Interval);

        if (debugging)
        {
            LOG_INFO("HitDistance = {0}, Result.Interval = {1}, Result.Point = {2}", hitDistance, result.Interval,
                     result.Point.ToString());
        }

        result.Normal = Vector3{1, 0, 0};
        result.FrontFace = true;
        result.Material = m_phaseFunction;

        return true;
    }

    AABB ConstantMedium::BoundingBox() const
    {
        return m_boundary->BoundingBox();
    }
}
