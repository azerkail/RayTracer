#include "AABB.h"

namespace RayTracer
{
    AABB::AABB(const Interval& x, const Interval& y, const Interval& z) : m_x{x}, m_y{y}, m_z{z}
    {
    }

    AABB::AABB(const Point3& first, const Point3& second)
    {
        m_x = first[0] <= second[0] ? Interval{first[0], second[0]} : Interval{second[0], first[0]};
        m_y = first[1] <= second[1] ? Interval{first[1], second[1]} : Interval{second[1], first[1]};
        m_z = first[2] <= second[2] ? Interval{first[2], second[2]} : Interval{second[2], first[2]};
    }

    AABB::AABB(const AABB& first, const AABB& second)
    {
        m_x = Interval{first.m_x, second.m_x};
        m_y = Interval{first.m_y, second.m_y};
        m_z = Interval(first.m_z, second.m_z);
    }

    const Interval& AABB::AxisInterval(const int number) const
    {
        if (number == 1)
        {
            return m_y;
        }

        if (number == 2)
        {
            return m_z;
        }

        return m_x;
    }

    bool AABB::Hit(const Ray& ray, Interval rayInterval) const
    {
        const Point3& rayOrigin = ray.Origin();
        const Vector3& rayDirection = ray.Direction();

        for (int axis = 0; axis < 3; axis++)
        {
            const Interval& axisInterval = AxisInterval(axis);
            const float adinv = 1.0f / rayDirection[axis];
            const float t0 = (axisInterval.GetMin() - rayOrigin[axis]) * adinv;
            const float t1 = (axisInterval.GetMax() - rayOrigin[axis]) * adinv;

            if (t0 < t1)
            {
                if (t0 > rayInterval.GetMin())
                {
                    rayInterval.SetMin(t0);
                }

                if (t1 < rayInterval.GetMax())
                {
                    rayInterval.SetMax(t1);
                }
            }
            else
            {
                if (t1 > rayInterval.GetMin())
                {
                    rayInterval.SetMin(t1);
                }

                if (t0 < rayInterval.GetMax())
                {
                    rayInterval.SetMax(t0);
                }
            }

            if (rayInterval.GetMax() <= rayInterval.GetMin())
            {
                return false;
            }
        }

        return true;
    }
} // RayTracer
