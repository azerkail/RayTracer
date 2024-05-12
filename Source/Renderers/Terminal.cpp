#include "Terminal.h"
#include "Converter.h"

namespace RayTracer {
    std::string Terminal::Render(const Color& pixel) const {
        float red = pixel.X();
        float green = pixel.Y();
        float blue = pixel.Z();

        int redAsRGB = RayTracer::ConvertToRGB(red);
        int greenAsRGB = RayTracer::ConvertToRGB(green);
        int blueAsRGB = RayTracer::ConvertToRGB(blue);

        return std::to_string(redAsRGB) + ' ' + std::to_string(greenAsRGB) + ' ' + std::to_string(blueAsRGB) + '\n';
    }
}
