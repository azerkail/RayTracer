#include "Engine.h"

#include "Logging/Log.h"
#include "Camera/Camera.h"
#include "Renderers/FileRenderer.h"
#include "Objects/Sphere.h"

namespace RayTracer {
    void Engine::Trace() {
        // Build the world.
        HittableVector world;

        world.Add(std::make_shared<Sphere>(Point3{0, 0, -1}, 0.5));
        world.Add(std::make_shared<Sphere>(Point3{0, -100.5, -1}, 100));

        Camera camera{std::make_unique<FileRenderer>()};

        camera.AspectRatio = 16.0f / 9.0f;
        camera.ImageWidth = 400;
        camera.SamplesPerPixel = 100;
        camera.MaxDepth = 50;

        camera.Render(world);
    }
}
