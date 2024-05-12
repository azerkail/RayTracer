#include "FileRenderer.h"
#include "Converter.h"
#include "Files/FileHandler.h"
#include "Logging/Log.h"

namespace RayTracer {
    void FileRenderer::Initialise(int imageWidth, int imageHeight) {
        m_image += "P3\n" + std::to_string(imageWidth) + ' ' + std::to_string(imageHeight) + "\n255\n";
    }

    void FileRenderer::Render(const Color& pixel) {
        float red = pixel.X();
        float green = pixel.Y();
        float blue = pixel.Z();

        int redAsRGB = RayTracer::ConvertToRGB(red);
        int greenAsRGB = RayTracer::ConvertToRGB(green);
        int blueAsRGB = RayTracer::ConvertToRGB(blue);

        m_image += std::to_string(redAsRGB) + ' ' + std::to_string(greenAsRGB) + ' ' + std::to_string(blueAsRGB) + '\n';
    }

    void FileRenderer::Terminate() const {
        LOG_INFO(m_image);
        FileHandler::WriteToFile(m_image);
    }
}
