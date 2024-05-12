#ifndef RAYTRACER_FILEHANDLER_H
#define RAYTRACER_FILEHANDLER_H

#include <string>

namespace RayTracer {

    class FileHandler {
    public:
        static std::string ProducePPMImage();
        static void WriteToFile(const std::string& contents);

    private:
        inline static const std::string& m_fileName = "image.ppm";
        inline static const int m_baseImageWidth = 256;
        inline static const int m_baseImageHeight = 256;
        inline static const double m_rgbConversionValue = 255.999;
    };

}

#endif //RAYTRACER_FILEHANDLER_H
