#include "Interval.h"

namespace RayTracer
{
    Interval::Interval() : m_min(+Constants::Infinity), m_max(-Constants::Infinity)
    {
    }

    Interval::Interval(const float min, const float max) : m_min(min), m_max(max)
    {
    }

    Interval::Interval(const Interval& first, const Interval& second)
    {
        m_min = first.Min() <= second.Min() ? first.Min() : second.Min();
        m_max = first.Max() >= second.Max() ? first.Max() : second.Max();
    }

    float Interval::Min() const
    {
        return m_min;
    }

    float Interval::Max() const
    {
        return m_max;
    }

    void Interval::SetMin(const float min)
    {
        m_min = min;
    }

    void Interval::SetMax(const float max)
    {
        m_max = max;
    }

    float Interval::Size() const
    {
        return m_max - m_min;
    }

    float Interval::Clamp(const float value) const
    {
        if (value < m_min)
        {
            return m_min;
        }

        if (value > m_max)
        {
            return m_max;
        }

        return value;
    }

    bool Interval::Contains(const float value) const
    {
        return m_min <= value && value <= m_max;
    }

    bool Interval::Surrounds(const float value) const
    {
        return m_min < value && value < m_max;
    }

    Interval Interval::Expand(const float delta) const
    {
        const float padding = delta / 2;
        return Interval{m_min - padding, m_max + padding};
    }

    Interval operator+(const Interval& interval, const float displacement)
    {
        return Interval{interval.Min() + displacement, interval.Max() + displacement};
    }

    Interval operator+(const float displacement, const Interval& interval)
    {
        return interval + displacement;
    }
}
