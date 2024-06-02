#include "Engine.h"

#include "BVH/BVHNode.h"
#include "Renderers/FileRenderer.h"
#include "Objects/Sphere.h"
#include "Materials/Lambertian.h"
#include "Materials/Metal.h"
#include "Materials/Dieletric.h"
#include "Textures/CheckerTexture.h"

namespace RayTracer
{
    void Engine::Trace()
    {
        const HittableVector& world = CreateWorld();
        Camera camera = CreateCamera();

        camera.Render(world);
    }

    HittableVector Engine::CreateWorld()
    {
        HittableVector world;

        auto checker = std::make_shared<CheckerTexture>(0.32f, Color{0.2f, 0.3f, 0.1f}, Color{0.9f, 0.9f, 0.9f});
        auto groundMaterial = std::make_shared<Lambertian>(checker);
        world.Add(std::make_shared<Sphere>(Point3{0, -1000.0f, 0}, 1000, groundMaterial));

        const auto offsetPoint = Point3{4, 0.2f, 0};
        for (int a = -11; a < 11; a++)
        {
            for (int b = -11; b < 11; b++)
            {
                const auto aAsFloat = static_cast<float>(a);
                const auto bAsFloat = static_cast<float>(b);
                Point3 center{
                    aAsFloat + 0.9f * Utilities::RandomFloat(), 0.2f,
                    bAsFloat + 0.9f * Utilities::RandomFloat()
                };

                if ((center - offsetPoint).Length() > 0.9)
                {
                    const float chooseMaterial = Utilities::RandomFloat();
                    std::shared_ptr<Sphere> sphere;

                    if (chooseMaterial < 0.8)
                    {
                        // Diffuse.
                        Color albedo = Random() * Random();
                        auto sphereMaterial = std::make_shared<Lambertian>(albedo);
                        auto targetSphere = center + Vector3{0, Utilities::RandomFloat(0, 0.5), 0};
                        sphere = std::make_shared<Sphere>(center, targetSphere, 0.2f, sphereMaterial);
                    }
                    else if (chooseMaterial < 0.95)
                    {
                        // Metal.
                        Color albedo = Random(0.5, 1);
                        auto fuzz = Utilities::RandomFloat(0, 0.5);
                        auto sphereMaterial = std::make_shared<Metal>(albedo, fuzz);
                        sphere = std::make_shared<Sphere>(center, 0.2f, sphereMaterial);
                    }
                    else
                    {
                        // Glass.
                        auto sphereMaterial = std::make_shared<Dielectric>(1.5);
                        sphere = std::make_shared<Sphere>(center, 0.2f, sphereMaterial);
                    }

                    world.Add(sphere);
                }
            }
        }

        auto largeSphere1Material = std::make_shared<Dielectric>(1.5);
        world.Add(std::make_shared<Sphere>(Point3{0, 1, 0}, 1.0, largeSphere1Material));

        auto largeSphere2Material = std::make_shared<Lambertian>(Color{0.4f, 0.2f, 0.1f});
        world.Add(std::make_shared<Sphere>(Point3{-4, 1, 0}, 1.0, largeSphere2Material));

        auto largeSphere3Material = std::make_shared<Metal>(Color{0.7f, 0.6f, 0.5f}, 0.0f);
        world.Add(std::make_shared<Sphere>(Point3{4, 1, 0}, 1.0, largeSphere3Material));

        world = HittableVector{std::make_shared<BVHNode>(world)};

        return world;
    }

    Camera Engine::CreateCamera()
    {
        Camera camera{std::make_unique<FileRenderer>()};

        camera.AspectRatio = 16.0f / 9.0f;
        camera.ImageWidth = 640; // This produces a 640x360 image.
        camera.SamplesPerPixel = 100;
        camera.MaxDepth = 50;
        camera.VerticalFOV = 20;
        camera.LookFrom = Point3{13, 2, 3};
        camera.LookAt = Point3{0, 0, 0};
        camera.Up = Vector3{0, 1, 0};
        camera.DefocusAngle = 0.6f;
        camera.FocusDistance = 10.0f;

        return camera;
    }
}
