#include "RotateY.h"

namespace RayTracer
{
    RotateY::RotateY(std::shared_ptr<IHittable> object, const float angle) : m_object(std::move(object))
    {
        const float radians = Utilities::DegreesToRadians(angle);

        m_sinTheta = std::sin(radians);
        m_cosTheta = std::cos(radians);
        m_boundingBox = m_object->BoundingBox();

        Point3 min{Constants::Infinity, Constants::Infinity, Constants::Infinity};
        Point3 max{-Constants::Infinity, -Constants::Infinity, -Constants::Infinity};

        for (int i = 0; i < 2; ++i)
        {
            const auto iAsFloat = static_cast<float>(i);

            for (int j = 0; j < 2; ++j)
            {
                const auto jAsFloat = static_cast<float>(j);

                for (int k = 0; k < 2; ++k)
                {
                    const auto kAsFloat = static_cast<float>(k);
                    const float x = iAsFloat * m_boundingBox.X().Max() + (1 - iAsFloat) * m_boundingBox.X().Min();
                    const float y = jAsFloat * m_boundingBox.Y().Max() + (1 - jAsFloat) * m_boundingBox.Y().Min();
                    const float z = kAsFloat * m_boundingBox.Z().Max() + (1 - kAsFloat) * m_boundingBox.Z().Min();

                    const float newX = m_cosTheta * x + m_sinTheta * z;
                    const float newZ = -m_sinTheta * x + m_cosTheta * z;

                    Vector3 tester{newX, y, newZ};

                    for (int c = 0; c < 3; ++c)
                    {
                        min[c] = std::fmin(min[c], tester[c]);
                        max[c] = std::fmax(max[c], tester[c]);
                    }
                }
            }
        }

        m_boundingBox = AABB{min, max};
    }

    bool RotateY::Hit(const Ray& ray, const Interval interval, HitResult& result) const
    {
        Vector3 origin = ray.Origin();
        Vector3 direction = ray.Direction();

        origin[0] = m_cosTheta * ray.Origin()[0] - m_sinTheta * ray.Origin()[2];
        origin[2] = m_sinTheta * ray.Origin()[0] + m_cosTheta * ray.Origin()[2];

        direction[0] = m_cosTheta * ray.Direction()[0] - m_sinTheta * ray.Direction()[2];
        direction[2] = m_sinTheta * ray.Direction()[0] + m_cosTheta * ray.Direction()[2];

        const Ray rotatedRay{origin, direction, ray.Time()};

        if (!m_object->Hit(rotatedRay, interval, result))
        {
            return false;
        }

        Point3 point = result.Point;
        point[0] = m_cosTheta * result.Point[0] + m_sinTheta * result.Point[2];
        point[2] = -m_sinTheta * result.Point[0] + m_cosTheta * result.Point[2];

        Vector3 normal = result.Normal;
        normal[0] = m_cosTheta * result.Normal[0] + m_sinTheta * result.Normal[2];
        normal[2] = -m_sinTheta * result.Normal[0] + m_cosTheta * result.Normal[2];

        result.Point = point;
        result.Normal = normal;

        return true;
    }

    AABB RotateY::BoundingBox() const
    {
        return m_boundingBox;
    }
}
