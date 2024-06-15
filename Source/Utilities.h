#ifndef RAYTRACER_UTILITIES_H
#define RAYTRACER_UTILITIES_H

#include <random>
#include "Collections/HittableVector.h"
#include "Objects/Quad.h"

namespace RayTracer
{
    class Utilities
    {
    public:
        // Disallow creating this class as it should only hold public static methods.
        Utilities() = delete;

        static int ConvertToRGB(const float value)
        {
            return static_cast<int>(Constants::RGBConversionValue * value);
        }

        static float DegreesToRadians(const float degrees)
        {
            return degrees * Constants::Pi / 180.0f;
        }

        static float RandomFloat()
        {
            static std::uniform_real_distribution<float> distribution(0.0, 1.0);
            static std::mt19937 generator{std::random_device{}()};
            return distribution(generator);
        }

        static float RandomFloat(const float min, const float max)
        {
            return min + (max - min) * RandomFloat();
        }

        static int RandomInt(const int min, const int max)
        {
            const auto minAsFloat = static_cast<float>(min);
            const auto maxAsFloat = static_cast<float>(max);
            return static_cast<int>(RandomFloat(minAsFloat, maxAsFloat + 1));
        }

        static float LinearToGamma(const float linearComponent)
        {
            if (linearComponent > 0)
            {
                return std::sqrt(linearComponent);
            }

            return 0;
        }

        static HittableVector Box(const Point3& a, const Point3& b,
                                  const std::shared_ptr<IMaterial>& material)
        {
            HittableVector sides;

            const Point3 min{std::fmin(a.X(), b.X()), std::fmin(a.Y(), b.Y()), std::fmin(a.Z(), b.Z())};
            const Point3 max{std::fmax(a.X(), b.X()), std::fmax(a.Y(), b.Y()), std::fmax(a.Z(), b.Z())};

            const Vector3 xDelta{max.X() - min.X(), 0, 0};
            const Vector3 yDelta{0, max.Y() - min.Y(), 0};
            const Vector3 zDelta{0, 0, max.Z() - min.Z()};

            // Front.
            sides.Add(std::make_shared<Quad>(Point3{min.X(), min.Y(), max.Z()}, xDelta, yDelta, material));
            // Right.
            sides.Add(std::make_shared<Quad>(Point3{max.X(), min.Y(), max.Z()}, -zDelta, yDelta, material));
            // Back.
            sides.Add(std::make_shared<Quad>(Point3{max.X(), min.Y(), min.Z()}, -xDelta, yDelta, material));
            // Left.
            sides.Add(std::make_shared<Quad>(Point3{min.X(), min.Y(), min.Z()}, zDelta, yDelta, material));
            // Top.
            sides.Add(std::make_shared<Quad>(Point3{min.X(), max.Y(), max.Z()}, xDelta, -zDelta, material));
            // Bottom.
            sides.Add(std::make_shared<Quad>(Point3{min.X(), min.Y(), min.Z()}, xDelta, zDelta, material));

            return sides;
        }
    };
}

#endif //RAYTRACER_UTILITIES_H
