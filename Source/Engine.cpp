#include "Engine.h"
#include "Logging/Log.h"
#include "Camera/Camera.h"
#include "Renderers/FileRenderer.h"
#include "Collections/HittableVector.h"
#include "Objects/Sphere.h"

namespace RayTracer {
    void Engine::Initialise() {
        // Calculate viewport size.
        float aspectRatio = 16.0f / 9.0f;
        m_imageWidth = 400;

        // Make sure image height is always at least 1 pixel.
        m_imageHeight = m_imageWidth / static_cast<int>(aspectRatio);
        m_imageHeight = m_imageHeight < 1 ? 1 : m_imageHeight;

        m_camera.Initialise(m_imageWidth, m_imageHeight);
        m_renderer = std::make_unique<FileRenderer>(m_camera, m_imageWidth, m_imageHeight);
    }

    void Engine::Trace() {
        // Build the world.
        HittableVector world;

        world.Add(std::make_shared<Sphere>(Point3{0, 0, -1}, 0.5));
        world.Add(std::make_shared<Sphere>(Point3{0, -100.5, -1}, 100));

        // Ray tracer.
        auto pixelOrigin = m_camera.PixelOrigin();
        auto cameraCenter = m_camera.Center();
        auto pixelDeltaU = m_camera.PixelDeltaU();
        auto pixelDeltaV = m_camera.PixelDeltaV();

        for (int row = 0; row < m_imageHeight; ++row) {
            LOG_INFO("Lines remaining: {0}", m_imageHeight - row);

            auto rowAsFloat = static_cast<float>(row);

            for (int column = 0; column < m_imageWidth; ++column) {
                auto columnAsFloat = static_cast<float>(column);
                auto pixelCenter = pixelOrigin + (columnAsFloat * pixelDeltaU) + (rowAsFloat * pixelDeltaV);
                auto rayDirection = pixelCenter - cameraCenter;

                Ray ray{cameraCenter, rayDirection};
                Color color = Utilities::GetRayColor(ray, world);

                m_renderer->Render(color);
            }
        }

    }

    void Engine::Terminate() {
        m_renderer->Terminate();
    }
}
