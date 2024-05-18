#ifndef RAYTRACER_UTILITIES_H
#define RAYTRACER_UTILITIES_H

#include <random>
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

        inline static float RandomFloat() {
            static std::uniform_real_distribution<float> distribution(0.0, 1.0);
            static std::mt19937 generator{std::random_device{}()};
            return distribution(generator);
        }

        inline static float RandomFloat(float min, float max) {
            return min + (max - min) * RandomFloat();
        }

        inline static float LinearToGamma(float linearComponent) {
            if (linearComponent > 0) {
                return std::sqrt(linearComponent);
            }

            return 0;
        }
    };

}

#endif //RAYTRACER_UTILITIES_H
