#include <string>
#include "RayTracer.h"
#include "Logging/Log.h"
#include "Files/FileHandler.h"

namespace RayTracer {
    RayTracer::RayTracer(const RendererBase& renderer) : m_image{}, m_renderer(renderer) {}

    void RayTracer::Trace() {
        m_image += "P3\n" + std::to_string(m_baseImageWidth) + ' ' + std::to_string(m_baseImageHeight) + "\n255\n";

        for (int row = 0; row < m_baseImageHeight; ++row) {
            LOG_INFO("Lines remaining: {0}", m_baseImageHeight - row);

            auto rowAsFloat = static_cast<float>(row);

            for (int column = 0; column < m_baseImageWidth; ++column) {
                auto columnAsFloat = static_cast<float>(column);

                float red = rowAsFloat / (m_baseImageWidth - 1);
                float green = columnAsFloat / (m_baseImageHeight - 1);
                float blue = 0;

                auto pixelColor = Color{red, green, blue};

                m_image += m_renderer.Render(pixelColor);
            }
        }

        LOG_INFO(m_image);
    }

    void RayTracer::Finish() {
        FileHandler::WriteToFile(m_image);
    }
}
