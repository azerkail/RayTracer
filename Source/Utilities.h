#ifndef RAYTRACER_UTILITIES_H
#define RAYTRACER_UTILITIES_H

#include "Objects/Hittable.h"
#include "Collections/HittableVector.h"

namespace RayTracer {

    class Utilities {
    public:
        // Disallow creating this class as it should only hold public static methods.
        Utilities() = delete;

        inline static int ConvertToRGB(float value) {
            return static_cast<int>(Constants::RGBConversionValue * value);
        }

        inline static float DegreesToRadians(float degrees) {
            return degrees * Constants::Pi / 180.0f;
        }
    };

}

#endif //RAYTRACER_UTILITIES_H
