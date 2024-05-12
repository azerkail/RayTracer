#include "Converter.h"

namespace RayTracer {
    int ConvertToRGB(float value) {
        return static_cast<int>(RGBConversionValue * value);
    }
}
