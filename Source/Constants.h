#ifndef RAYTRACER_CONSTANTS_H
#define RAYTRACER_CONSTANTS_H

#include <limits>
#include "Maths/Interval.h"

namespace RayTracer {

    class Constants {
    public:
        // Disallow creating this class as it should only hold public constant values.
        Constants() = delete;

        constexpr static const float Infinity = std::numeric_limits<float>::infinity();
        constexpr static const float Pi = 3.1415926535897932385f;
        constexpr static const int RGBConversionValue = 256;
        inline static const Interval Empty{};
        inline static const Interval Universe{-Infinity, +Infinity};
    };

}

#endif //RAYTRACER_CONSTANTS_H
