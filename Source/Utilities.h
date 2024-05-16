#ifndef RAYTRACER_UTILITIES_H
#define RAYTRACER_UTILITIES_H

#include "Objects/Hittable.h"
#include "Collections/HittableVector.h"

namespace RayTracer {

    class Utilities {
    public:
        // Disallow creating this class as it should only hold public static methods.
        Utilities() = delete;

        inline static Color GetRayColor(const Ray& ray, const HittableVector& hittable) {
            HitResult result;
            if (hittable.Hit(ray, Interval{0, Constants::Infinity}, result)) {
                return 0.5 * (result.Normal + Color{1, 1, 1});
            }

            Vector3 unitDirection = UnitVector(ray.Direction());
            float alpha = 0.5f * (unitDirection.Y() + 1.0f);
            return (1 - alpha) * Color{1, 1, 1} + alpha * Color{0.5f, 0.7f, 1};
        }

        inline static int ConvertToRGB(float value) {
            return static_cast<int>(Constants::RGBConversionValue * value);
        }

        inline static float DegreesToRadians(float degrees) {
            return degrees * Constants::Pi / 180.0f;
        }
    };

}

#endif //RAYTRACER_UTILITIES_H
