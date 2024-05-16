#include "Interval.h"

namespace RayTracer {
    Interval::Interval() : m_min(+Constants::Infinity), m_max(-Constants::Infinity) {}

    Interval::Interval(float min, float max) : m_min(min), m_max(max) {}

    float Interval::GetMin() const {
        return m_min;
    }

    float Interval::GetMax() const {
        return m_max;
    }

    float Interval::Size() const {
        return m_max - m_min;
    }

    float Interval::Clamp(float value) const {
        if (value < m_min) {
            return m_min;
        }

        if (value > m_max) {
            return m_max;
        }

        return value;
    }

    bool Interval::Contains(float value) const {
        return m_min <= value && value <= m_max;
    }

    bool Interval::Surrounds(float value) const {
        return m_min < value && value < m_max;
    }
}
