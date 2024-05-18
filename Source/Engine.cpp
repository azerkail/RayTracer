#include "Engine.h"
#include "Camera/Camera.h"
#include "Renderers/FileRenderer.h"
#include "Objects/Sphere.h"
#include "Materials/Lambertian.h"
#include "Materials/Metal.h"

namespace RayTracer {
    void Engine::Trace() {
        // Build the world.
        HittableVector world;

        auto materialGround = std::make_shared<Lambertian>(Color{0.8f, 0.8f, 0.0f});
        auto materialCenter = std::make_shared<Lambertian>(Color{0.1f, 0.2f, 0.5f});
        auto materialLeft = std::make_shared<Metal>(Color{0.8f, 0.8f, 0.8f});
        auto materialRight = std::make_shared<Metal>(Color{0.8f, 0.6f, 0.2f});

        world.Add(std::make_shared<Sphere>(Point3{0.0f, -100.5f, -1.0f}, 100.0f, materialGround));
        world.Add(std::make_shared<Sphere>(Point3{0.0f, 0.0f, -1.2f}, 0.5f, materialCenter));
        world.Add(std::make_shared<Sphere>(Point3{-1.0f, 0.0f, -1.0f}, 0.5f, materialLeft));
        world.Add(std::make_shared<Sphere>(Point3{1.0f, 0.0f, -1.0f}, 0.5f, materialRight));

        Camera camera{std::make_unique<FileRenderer>()};

        camera.AspectRatio = 16.0f / 9.0f;
        camera.ImageWidth = 640; // This produces a 640x360 image.
        camera.SamplesPerPixel = 100;
        camera.MaxDepth = 50;

        camera.Render(world);
    }
}
