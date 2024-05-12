#include "Engine.h"
#include "Logging/Log.h"
#include "Camera/Camera.h"
#include "Maths/Ray.h"

namespace RayTracer {
    Engine::Engine(RendererBase& renderer) : m_renderer(renderer) {}

    void Engine::Trace() {
        // Calculate viewport size.
        float aspectRatio = 16.0 / 9.0;
        int imageWidth = 400;

        // Make sure image height is always at least 1 pixel.
        int imageHeight = imageWidth / static_cast<int>(aspectRatio);
        imageHeight = imageHeight < 1 ? 1 : imageHeight;

        m_renderer.Initialise(imageWidth, imageHeight);

        Camera camera{imageWidth, imageHeight};
        auto pixelOrigin = camera.PixelOrigin();
        auto cameraCenter = camera.Center();
        auto pixelDeltaU = camera.PixelDeltaU();
        auto pixelDeltaV = camera.PixelDeltaV();

        for (int row = 0; row < m_baseImageHeight; ++row) {
            LOG_INFO("Lines remaining: {0}", m_baseImageHeight - row);

            auto rowAsFloat = static_cast<float>(row);

            for (int column = 0; column < m_baseImageWidth; ++column) {
                auto columnAsFloat = static_cast<float>(column);
                auto pixelCenter = pixelOrigin + (columnAsFloat * pixelDeltaU) + (rowAsFloat * pixelDeltaV);
                auto rayDirection = pixelCenter - cameraCenter;

                Ray ray{cameraCenter, rayDirection};
                Color color = RayTracer::GetRayColor(ray);

                m_renderer.Render(color);
            }
        }

    }

    void Engine::Terminate() {
        m_renderer.Terminate();
    }
}
