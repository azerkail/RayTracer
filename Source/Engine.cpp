#include <string>
#include "Engine.h"
#include "Logging/Log.h"
#include "Files/FileHandler.h"
#include "Camera/Camera.h"
#include "Maths/Ray.h"

namespace RayTracer {
    Engine::Engine(const RendererBase& renderer) : m_image{}, m_renderer(renderer) {}

    void Engine::Trace() {
        // Calculate viewport size.
        float aspectRatio = 16.0 / 9.0;
        float imageWidth = 400;

        // Make sure image height is always at least 1 pixel.
        float imageHeight = imageWidth / aspectRatio;
        imageHeight = imageHeight < 1 ? 1 : imageHeight;

        Camera camera{imageWidth, imageHeight};
        auto pixelOrigin = camera.PixelOrigin();
        auto cameraCenter = camera.Center();
        auto pixelDeltaU = camera.PixelDeltaU();
        auto pixelDeltaV = camera.PixelDeltaV();

        m_image += "P3\n" + std::to_string(m_baseImageWidth) + ' ' + std::to_string(m_baseImageHeight) + "\n255\n";

        for (int row = 0; row < m_baseImageHeight; ++row) {
            LOG_INFO("Lines remaining: {0}", m_baseImageHeight - row);

            auto rowAsFloat = static_cast<float>(row);

            for (int column = 0; column < m_baseImageWidth; ++column) {
                auto columnAsFloat = static_cast<float>(column);
                auto pixelCenter = pixelOrigin + (columnAsFloat * pixelDeltaU) + (rowAsFloat * pixelDeltaV);
                auto rayDirection = pixelCenter - cameraCenter;

                Ray ray{cameraCenter, rayDirection};
                Color color = RayTracer::GetRayColor(ray);

                m_image += m_renderer.Render(color);
            }
        }

        LOG_INFO(m_image);
    }

    void Engine::Finish() {
        FileHandler::WriteToFile(m_image);
    }
}
