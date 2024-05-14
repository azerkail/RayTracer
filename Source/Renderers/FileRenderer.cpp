#include "FileRenderer.h"
#include "Files/FileHandler.h"
#include "Logging/Log.h"
#include "Utilities.h"

namespace RayTracer {
    FileRenderer::FileRenderer(const Camera& camera, int imageWidth, int imageHeight) : m_camera(camera) {
        m_image += "P3\n" + std::to_string(imageWidth) + ' ' + std::to_string(imageHeight) + "\n255\n";
    }

    void FileRenderer::Render(const Color& pixel) {
        float red = pixel.X();
        float green = pixel.Y();
        float blue = pixel.Z();

        int redAsRGB = Utilities::ConvertToRGB(red);
        int greenAsRGB = Utilities::ConvertToRGB(green);
        int blueAsRGB = Utilities::ConvertToRGB(blue);

        m_image += std::to_string(redAsRGB) + ' ' + std::to_string(greenAsRGB) + ' ' + std::to_string(blueAsRGB) + '\n';
    }

    void FileRenderer::Terminate() const {
        LOG_INFO(m_image);
        FileHandler::WriteToFile(m_image);
    }
}
