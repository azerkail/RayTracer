#ifndef RAYTRACER_FILEHANDLER_H
#define RAYTRACER_FILEHANDLER_H

#include <string>

namespace RayTracer {

    class FileHandler {
    public:
        static void WriteToFile(const std::string& contents);

    private:
        inline static const std::string& m_fileName = "image.ppm";
    };

}

#endif //RAYTRACER_FILEHANDLER_H
