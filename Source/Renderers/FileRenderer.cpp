#include "FileRenderer.h"
#include "Files/FileHandler.h"
#include "Utilities.h"

namespace RayTracer {
    void FileRenderer::Initialise(int imageWidth, int imageHeight) {
        m_image += "P3\n" + std::to_string(imageWidth) + ' ' + std::to_string(imageHeight) + "\n255\n";
    }

    void FileRenderer::Render(const Color& pixel) {
        float red = pixel.X();
        float green = pixel.Y();
        float blue = pixel.Z();

        // Convert from linear space to gamma space.
        red = Utilities::LinearToGamma(red);
        green = Utilities::LinearToGamma(green);
        blue = Utilities::LinearToGamma(blue);

        // Convert from [0,1] range to [0,255] range.
        static const Interval intensity{0.000f, 0.999f};
        int redAsRGB = Utilities::ConvertToRGB(intensity.Clamp(red));
        int greenAsRGB = Utilities::ConvertToRGB(intensity.Clamp(green));
        int blueAsRGB = Utilities::ConvertToRGB(intensity.Clamp(blue));

        m_image += std::to_string(redAsRGB) + ' ' + std::to_string(greenAsRGB) + ' ' + std::to_string(blueAsRGB) + '\n';
    }

    void FileRenderer::Terminate() const {
        LOG_INFO(m_image);
        FileHandler::WriteToFile(m_image);
    }
}
