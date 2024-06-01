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
        m_min = first.GetMin() <= second.GetMin() ? first.GetMin() : second.GetMin();
        m_max = second.GetMax() >= first.GetMax() ? first.GetMax() : second.GetMax();
    }

    float Interval::GetMin() const
    {
        return m_min;
    }

    float Interval::GetMax() const
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
        float padding = delta / 2;
        return Interval{m_min - padding, m_max + padding};
    }
}
