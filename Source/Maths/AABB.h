#ifndef AABB_H
#define AABB_H

#include "Interval.h"
#include "Ray.h"
#include "Vector3.h"

namespace RayTracer
{
    class AABB
    {
    public:
        AABB() = default;
        AABB(const Interval& x, const Interval& y, const Interval& z);
        AABB(const Point3& first, const Point3& second);
        AABB(const AABB& first, const AABB& second);

        [[nodiscard]] Interval X() const;
        [[nodiscard]] Interval Y() const;
        [[nodiscard]] Interval Z() const;

        [[nodiscard]] const Interval& AxisInterval(int number) const;
        [[nodiscard]] bool Hit(const Ray& ray, Interval rayInterval) const;
        [[nodiscard]] int LongestAxis() const;

    private:
        Interval m_x, m_y, m_z;

        void PadToMinimums();
    };

    AABB operator+(const AABB& boundingBox, const Vector3& offset);
    AABB operator+(const Vector3& offset, const AABB& boundingBox);
}

#endif // AABB_H
