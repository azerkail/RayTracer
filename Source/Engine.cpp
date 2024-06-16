#include "Engine.h"

#include "BVH/BVHNode.h"
#include "Renderers/FileRenderer.h"
#include "Objects/Sphere.h"
#include "Materials/Lambertian.h"
#include "Materials/Metal.h"
#include "Materials/Dieletric.h"
#include "Materials/DiffuseLight.h"
#include "Objects/ConstantMedium.h"
#include "Objects/Quad.h"
#include "Objects/RotateY.h"
#include "Objects/Translate.h"
#include "Textures/CheckerTexture.h"
#include "Textures/ImageTexture.h"
#include "Textures/NoiseTexture.h"

namespace RayTracer
{
    void Engine::Trace()
    {
        std::unique_ptr<HittableVector> world;
        std::unique_ptr<Camera> camera;

        switch (10)
        {
        case 1:
            world = std::make_unique<HittableVector>(CreateBouncingSpheres());
            camera = std::make_unique<Camera>(CreateBouncingSpheresCamera());
            break;
        case 2:
            world = std::make_unique<HittableVector>(CreateCheckeredSpheres());
            camera = std::make_unique<Camera>(CreateCheckeredSpheresCamera());
            break;
        case 3:
            world = std::make_unique<HittableVector>(CreateEarth());
            camera = std::make_unique<Camera>(CreateEarthCamera());
            break;
        case 4:
            world = std::make_unique<HittableVector>(CreatePerlinSpheres());
            camera = std::make_unique<Camera>(CreatePerlinSpheresCamera());
            break;
        case 5:
            world = std::make_unique<HittableVector>(CreateQuads());
            camera = std::make_unique<Camera>(CreateQuadsCamera());
            break;
        case 6:
            world = std::make_unique<HittableVector>(CreateSimpleLight());
            camera = std::make_unique<Camera>(CreateSimpleLightCamera());
            break;
        case 7:
            world = std::make_unique<HittableVector>(CreateCornellBox());
            camera = std::make_unique<Camera>(CreateCornellBoxCamera());
            break;
        case 8:
            world = std::make_unique<HittableVector>(CreateCornellSmoke());
            camera = std::make_unique<Camera>(CreateCornellSmokeCamera());
            break;
        case 9:
            world = std::make_unique<HittableVector>(CreateFinalScene());
            camera = std::make_unique<Camera>(CreateFinalSceneCamera(1920, 10000, 40));
            break;
        default:
            world = std::make_unique<HittableVector>(CreateFinalScene());
            camera = std::make_unique<Camera>(CreateFinalSceneCamera(640, 250, 4));
            return;
        }

        camera->Render(*world);
    }

    HittableVector Engine::CreateBouncingSpheres()
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

    Camera Engine::CreateBouncingSpheresCamera()
    {
        Camera camera{std::make_unique<FileRenderer>()};

        camera.AspectRatio = 16.0f / 9.0f;
        camera.ImageWidth = 640; // This produces a 640x360 image.
        camera.SamplesPerPixel = 100;
        camera.MaxDepth = 50;
        camera.Background = Color{0.7f, 0.8f, 1};
        camera.VerticalFOV = 20;
        camera.LookFrom = Point3{13, 2, 3};
        camera.LookAt = Point3{0, 0, 0};
        camera.Up = Vector3{0, 1, 0};
        camera.DefocusAngle = 0.6f;
        camera.FocusDistance = 10.0f;

        return camera;
    }

    HittableVector Engine::CreateCheckeredSpheres()
    {
        HittableVector world;

        auto checker = std::make_shared<CheckerTexture>(0.32f, Color{0.2f, 0.3f, 0.1f}, Color{0.9f, 0.9f, 0.9f});

        world.Add(std::make_shared<Sphere>(Point3{0, -10, 0}, 10, std::make_shared<Lambertian>(checker)));
        world.Add(std::make_shared<Sphere>(Point3{0, 10, 0}, 10, std::make_shared<Lambertian>(checker)));

        return world;
    }

    Camera Engine::CreateCheckeredSpheresCamera()
    {
        Camera camera{std::make_unique<FileRenderer>()};

        camera.AspectRatio = 16.0f / 9.0f;
        camera.ImageWidth = 640; // This produces a 640x360 image.
        camera.SamplesPerPixel = 100;
        camera.MaxDepth = 50;
        camera.Background = Color{0.7f, 0.8f, 1};
        camera.VerticalFOV = 20;
        camera.LookFrom = Point3{13, 2, 3};
        camera.LookAt = Point3{0, 0, 0};
        camera.Up = Vector3{0, 1, 0};

        return camera;
    }

    HittableVector Engine::CreateEarth()
    {
        auto earthTexture = std::make_shared<ImageTexture>("earthmap.jpg");
        auto earthMaterial = std::make_shared<Lambertian>(earthTexture);
        const auto globe = std::make_shared<Sphere>(Point3{0, 0, 0}, 2, earthMaterial);
        return HittableVector{globe};
    }

    Camera Engine::CreateEarthCamera()
    {
        Camera camera{std::make_unique<FileRenderer>()};

        camera.AspectRatio = 16.0f / 9.0f;
        camera.ImageWidth = 640; // This produces a 640x360 image.
        camera.SamplesPerPixel = 100;
        camera.MaxDepth = 50;
        camera.Background = Color{0.7f, 0.8f, 1};
        camera.VerticalFOV = 20;
        camera.LookFrom = Point3{0, 0, 12};
        camera.LookAt = Point3{0, 0, 0};
        camera.Up = Vector3{0, 1, 0};
        camera.DefocusAngle = 0;

        return camera;
    }

    HittableVector Engine::CreatePerlinSpheres()
    {
        HittableVector world;

        auto perlinTexture = std::make_shared<NoiseTexture>(4);

        world.Add(std::make_shared<Sphere>(Point3(0, -1000, 0), 1000, std::make_shared<Lambertian>(perlinTexture)));
        world.Add(std::make_shared<Sphere>(Point3(0, 2, 0), 2, std::make_shared<Lambertian>(perlinTexture)));

        return world;
    }

    Camera Engine::CreatePerlinSpheresCamera()
    {
        Camera camera{std::make_unique<FileRenderer>()};

        camera.AspectRatio = 16.0f / 9.0f;
        camera.ImageWidth = 640; // This produces a 640x360 image.
        camera.SamplesPerPixel = 100;
        camera.MaxDepth = 50;
        camera.Background = Color{0.7f, 0.8f, 1};
        camera.VerticalFOV = 20;
        camera.LookFrom = Point3{13, 2, 3};
        camera.LookAt = Point3{0, 0, 0};
        camera.Up = Vector3{0, 1, 0};
        camera.DefocusAngle = 0;

        return camera;
    }

    HittableVector Engine::CreateQuads()
    {
        HittableVector world;

        auto leftRed = std::make_shared<Lambertian>(Color{1.0f, 0.2f, 0.2f});
        auto backGreen = std::make_shared<Lambertian>(Color{0.2f, 1.0f, 0.2f});
        auto rightBlue = std::make_shared<Lambertian>(Color{0.2f, 0.2f, 1.0f});
        auto upperOrange = std::make_shared<Lambertian>(Color{1.0f, 0.5f, 0.0f});
        auto lowerTeal = std::make_shared<Lambertian>(Color{0.2f, 0.8f, 0.8f});

        world.Add(std::make_shared<Quad>(Point3{-3, -2, 5}, Vector3{0, 0, -4}, Vector3{0, 4, 0}, leftRed));
        world.Add(std::make_shared<Quad>(Point3{-2, -2, 0}, Vector3{4, 0, 0}, Vector3{0, 4, 0}, backGreen));
        world.Add(std::make_shared<Quad>(Point3{3, -2, 1}, Vector3{0, 0, 4}, Vector3{0, 4, 0}, rightBlue));
        world.Add(std::make_shared<Quad>(Point3{-2, 3, 1}, Vector3{4, 0, 0}, Vector3{0, 0, 4}, upperOrange));
        world.Add(std::make_shared<Quad>(Point3{-2, -3, 5}, Vector3{4, 0, 0}, Vector3{0, 0, -4}, lowerTeal));

        return world;
    }

    Camera Engine::CreateQuadsCamera()
    {
        Camera camera{std::make_unique<FileRenderer>()};

        camera.AspectRatio = 1.0;
        camera.ImageWidth = 640; // This produces a 640x360 image.
        camera.SamplesPerPixel = 100;
        camera.MaxDepth = 50;
        camera.Background = Color{0.7f, 0.8f, 1};
        camera.VerticalFOV = 80;
        camera.LookFrom = Point3{0, 0, 9};
        camera.LookAt = Point3{0, 0, 0};
        camera.Up = Vector3{0, 1, 0};
        camera.DefocusAngle = 0;

        return camera;
    }

    HittableVector Engine::CreateSimpleLight()
    {
        HittableVector world;

        const auto perlinTexture = std::make_shared<NoiseTexture>(4);

        world.Add(std::make_shared<Sphere>(Point3{0, -1000, 0}, 1000, std::make_shared<Lambertian>(perlinTexture)));
        world.Add(std::make_shared<Sphere>(Point3{0, 2, 0}, 2, std::make_shared<Lambertian>(perlinTexture)));

        const auto diffuseLight = std::make_shared<DiffuseLight>(Color{4, 4, 4});

        world.Add(std::make_shared<Sphere>(Point3{0, 7, 0}, 2, diffuseLight));
        world.Add(std::make_shared<Quad>(Point3{3, 1, -2}, Vector3{2, 0, 0}, Vector3{0, 2, 0}, diffuseLight));

        return world;
    }

    Camera Engine::CreateSimpleLightCamera()
    {
        Camera camera{std::make_unique<FileRenderer>()};

        camera.AspectRatio = 16.0f / 9.0f;
        camera.ImageWidth = 640; // This produces a 640x360 image.
        camera.SamplesPerPixel = 100;
        camera.MaxDepth = 50;
        camera.Background = Color{0, 0, 0};
        camera.VerticalFOV = 20;
        camera.LookFrom = Point3{26, 3, 6};
        camera.LookAt = Point3{0, 2, 0};
        camera.Up = Vector3{0, 1, 0};
        camera.DefocusAngle = 0;

        return camera;
    }

    HittableVector Engine::CreateCornellBox()
    {
        HittableVector world;

        const auto red = std::make_shared<Lambertian>(Color{0.65f, 0.05f, 0.05f});
        const auto white = std::make_shared<Lambertian>(Color{0.73f, 0.73f, 0.73f});
        const auto green = std::make_shared<Lambertian>(Color{0.12f, 0.45f, 0.15f});
        const auto light = std::make_shared<DiffuseLight>(Color{15, 15, 15});

        world.Add(std::make_shared<Quad>(Point3{555, 0, 0}, Vector3{0, 555, 0}, Vector3{0, 0, 555}, green));
        world.Add(std::make_shared<Quad>(Point3{0, 0, 0}, Vector3{0, 555, 0}, Vector3{0, 0, 555}, red));
        world.Add(std::make_shared<Quad>(Point3{343, 554, 332}, Vector3{-130, 0, 0}, Vector3{0, 0, -105}, light));
        world.Add(std::make_shared<Quad>(Point3{0, 0, 0}, Vector3{555, 0, 0}, Vector3{0, 0, 555}, white));
        world.Add(std::make_shared<Quad>(Point3{555, 555, 555}, Vector3{-555, 0, 0}, Vector3{0, 0, -555}, white));
        world.Add(std::make_shared<Quad>(Point3{0, 0, 555}, Vector3{555, 0, 0}, Vector3{0, 555, 0}, white));

        std::shared_ptr<IHittable> box1 = Utilities::Box(Point3{0, 0, 0}, Point3{165, 330, 165}, white);
        box1 = std::make_shared<RotateY>(box1, 15);
        box1 = std::make_shared<Translate>(box1, Vector3{265, 0, 295});
        world.Add(box1);

        std::shared_ptr<IHittable> box2 = Utilities::Box(Point3{0, 0, 0}, Point3{165, 165, 165}, white);
        box2 = std::make_shared<RotateY>(box2, -18);
        box2 = std::make_shared<Translate>(box2, Vector3{130, 0, 65});
        world.Add(box2);

        return world;
    }

    Camera Engine::CreateCornellBoxCamera()
    {
        Camera camera{std::make_unique<FileRenderer>()};

        camera.AspectRatio = 1.0f;
        camera.ImageWidth = 640; // This produces a 640x360 image.
        camera.SamplesPerPixel = 200;
        camera.MaxDepth = 50;
        camera.Background = Color{0, 0, 0};
        camera.VerticalFOV = 40;
        camera.LookFrom = Point3{278, 278, -800};
        camera.LookAt = Point3{278, 278, 0};
        camera.Up = Vector3{0, 1, 0};
        camera.DefocusAngle = 0;

        return camera;
    }

    HittableVector Engine::CreateCornellSmoke()
    {
        HittableVector world;

        const auto red = std::make_shared<Lambertian>(Color{0.65f, 0.05f, 0.05f});
        const auto white = std::make_shared<Lambertian>(Color{0.73f, 0.73f, 0.73f});
        const auto green = std::make_shared<Lambertian>(Color{0.12f, 0.45f, 0.15f});
        const auto light = std::make_shared<DiffuseLight>(Color{7, 7, 7});

        world.Add(std::make_shared<Quad>(Point3{555, 0, 0}, Vector3{0, 555, 0}, Vector3{0, 0, 555}, green));
        world.Add(std::make_shared<Quad>(Point3{0, 0, 0}, Vector3{0, 555, 0}, Vector3{0, 0, 555}, red));
        world.Add(std::make_shared<Quad>(Point3{113, 554, 127}, Vector3{330, 0, 0}, Vector3{0, 0, 305}, light));
        world.Add(std::make_shared<Quad>(Point3{0, 555, 0}, Vector3{550, 0, 0}, Vector3{0, 0, 555}, white));
        world.Add(std::make_shared<Quad>(Point3{0, 0, 0}, Vector3{550, 0, 0}, Vector3{0, 0, 555}, white));
        world.Add(std::make_shared<Quad>(Point3{0, 0, 555}, Vector3{555, 0, 0}, Vector3{0, 555, 0}, white));

        std::shared_ptr<IHittable> box1 = Utilities::Box(Point3{0, 0, 0}, Point3{165, 330, 165}, white);
        box1 = std::make_shared<RotateY>(box1, 15);
        box1 = std::make_shared<Translate>(box1, Vector3{265, 0, 295});

        std::shared_ptr<IHittable> box2 = Utilities::Box(Point3{0, 0, 0}, Point3{165, 165, 165}, white);
        box2 = std::make_shared<RotateY>(box2, -18);
        box2 = std::make_shared<Translate>(box2, Vector3{130, 0, 65});

        world.Add(std::make_shared<ConstantMedium>(box1, 0.01f, Color{0, 0, 0}));
        world.Add(std::make_shared<ConstantMedium>(box2, 0.01f, Color{1, 1, 1}));

        return world;
    }

    Camera Engine::CreateCornellSmokeCamera()
    {
        Camera camera{std::make_unique<FileRenderer>()};

        camera.AspectRatio = 1.0f;
        camera.ImageWidth = 640; // This produces a 640x360 image.
        camera.SamplesPerPixel = 200;
        camera.MaxDepth = 50;
        camera.Background = Color{0, 0, 0};
        camera.VerticalFOV = 40;
        camera.LookFrom = Point3{278, 278, -800};
        camera.LookAt = Point3{278, 278, 0};
        camera.Up = Vector3{0, 1, 0};
        camera.DefocusAngle = 0;

        return camera;
    }

    HittableVector Engine::CreateFinalScene()
    {
        HittableVector boxes1;

        const auto ground = std::make_shared<Lambertian>(Color{0.48f, 0.83f, 0.53f});
        constexpr int boxesPerSide = 20;

        for (int i = 0; i < boxesPerSide; ++i)
        {
            const auto iAsFloat = static_cast<float>(i);

            for (int j = 0; j < boxesPerSide; ++j)
            {
                constexpr float w = 100.0f;
                const auto jAsFloat = static_cast<float>(j);
                const float x0 = -1000.0f + iAsFloat * w;
                const float z0 = -1000.0f + jAsFloat * w;
                constexpr float y0 = 0.0f;
                const float x1 = x0 + w;
                const float y1 = Utilities::RandomFloat(1, 101);
                const float z1 = z0 + w;

                boxes1.Add(Utilities::Box(Point3{x0, y0, z0}, Point3{x1, y1, z1}, ground));
            }
        }

        HittableVector world;

        world.Add(std::make_shared<BVHNode>(boxes1));

        const auto light = std::make_shared<DiffuseLight>(Color{7, 7, 7});

        world.Add(std::make_shared<Quad>(Point3{123, 554, 147}, Vector3{300, 0, 0}, Vector3{0, 0, 265}, light));

        const Point3 center1{400, 400, 200};
        const Point3 center2 = center1 + Vector3{30, 0, 0};
        const auto sphereMaterial = std::make_shared<Lambertian>(Color{0.7f, 0.3f, 0.1f});

        world.Add(std::make_shared<Sphere>(center1, center2, 50, sphereMaterial));
        world.Add(std::make_shared<Sphere>(Point3{0, 150, 145}, 50,
                                           std::make_shared<Metal>(Color{0.8f, 0.8f, 0.9f}, 1.0f)));

        auto boundary = std::make_shared<Sphere>(Point3{360, 150, 145}, 70, std::make_shared<Dielectric>(1.5f));

        world.Add(boundary);
        world.Add(std::make_shared<ConstantMedium>(boundary, 0.2f, Color{0.2f, 0.4f, 0.9f}));

        boundary = std::make_shared<Sphere>(Point3{0, 0, 0}, 5000, std::make_shared<Dielectric>(1.5f));

        world.Add(std::make_shared<ConstantMedium>(boundary, 0.0001f, Color{1, 1, 1}));

        const auto earthMaterial = std::make_shared<Lambertian>(std::make_shared<ImageTexture>("earthmap.jpg"));

        world.Add(std::make_shared<Sphere>(Point3{400, 200, 400}, 100, earthMaterial));

        const auto perlinTexture = std::make_shared<NoiseTexture>(0.2f);

        world.Add(std::make_shared<Sphere>(Point3{220, 280, 300}, 80, std::make_shared<Lambertian>(perlinTexture)));

        HittableVector boxes2;
        const auto white = std::make_shared<Lambertian>(Color{0.73f, 0.73f, 0.73f});
        constexpr int numberOfSpheres = 1000;

        for (int i = 0; i < numberOfSpheres; ++i)
        {
            boxes2.Add(std::make_shared<Sphere>(Random(0, 165), 10, white));
        }

        world.Add(std::make_shared<Translate>(std::make_shared<RotateY>(std::make_shared<BVHNode>(boxes2), 15),
                                              Vector3{-100, 270, 395}));

        return world;
    }

    Camera Engine::CreateFinalSceneCamera(const int imageWidth, const int samplesPerPixel, const int maxDepth)
    {
        Camera camera{std::make_unique<FileRenderer>()};

        camera.AspectRatio = 1.0f;
        camera.ImageWidth = imageWidth;
        camera.SamplesPerPixel = samplesPerPixel;
        camera.MaxDepth = maxDepth;
        camera.Background = Color{0, 0, 0};
        camera.VerticalFOV = 40;
        camera.LookFrom = Point3{478, 278, -600};
        camera.LookAt = Point3{278, 278, 0};
        camera.Up = Vector3{0, 1, 0};
        camera.DefocusAngle = 0;

        return camera;
    }
}
