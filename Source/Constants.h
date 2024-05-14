#ifndef RAYTRACER_CONSTANTS_H
#define RAYTRACER_CONSTANTS_H

#include <limits>

namespace RayTracer {

    class Constants {
    public:
        // Disallow creating this class as it should only hold public constant values.
        Constants() = delete;

        constexpr static const float Infinity = std::numeric_limits<float>::infinity();
        constexpr static const float Pi = 3.1415926535897932385;
        constexpr static const float RGBConversionValue = 255.999;
    };

}

#endif //RAYTRACER_CONSTANTS_H
