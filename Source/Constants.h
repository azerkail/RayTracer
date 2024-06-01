#ifndef RAYTRACER_CONSTANTS_H
#define RAYTRACER_CONSTANTS_H

#include <limits>

#include "Maths/AABB.h"
#include "Maths/Interval.h"

namespace RayTracer
{
    class Constants
    {
    public:
        // Disallow creating this class as it should only hold public constant m_values.
        Constants() = delete;

        constexpr static float Infinity = std::numeric_limits<float>::infinity();
        constexpr static float Pi = 3.1415926535897932385f;
        constexpr static int RGBConversionValue = 256;
        inline static const Interval IntervalEmpty{};
        inline static const Interval IntervalUniverse{-Infinity, +Infinity};
        inline static const AABB AABBEmpty{IntervalEmpty, IntervalEmpty, IntervalEmpty};
        inline static const AABB AABBUniverse{IntervalUniverse, IntervalUniverse, IntervalUniverse};
    };
}

#endif //RAYTRACER_CONSTANTS_H
