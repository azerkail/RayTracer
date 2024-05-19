#include "Engine.h"
#include "Camera/Camera.h"
#include "Renderers/FileRenderer.h"
#include "Objects/Sphere.h"
#include "Materials/Lambertian.h"
#include "Materials/Metal.h"
#include "Materials/Dieletric.h"

namespace RayTracer {
    void Engine::Trace() {
        // Build the world.
        HittableVector world;

        float radius = std::cos(Constants::Pi / 4);

        auto materialLeft = std::make_shared<Lambertian>(Color{0, 0, 1});
        auto materialRight = std::make_shared<Lambertian>(Color{1, 0, 0});

        world.Add(std::make_shared<Sphere>(Point3{-radius, 0, -1.0f}, radius, materialLeft));
        world.Add(std::make_shared<Sphere>(Point3{radius, 0, -1.0f}, radius, materialRight));

        Camera camera{std::make_unique<FileRenderer>()};

        camera.AspectRatio = 16.0f / 9.0f;
        camera.ImageWidth = 640; // This produces a 640x360 image.
        camera.SamplesPerPixel = 100;
        camera.MaxDepth = 50;
        camera.VerticalFOV = 90;

        camera.Render(world);
    }
}
