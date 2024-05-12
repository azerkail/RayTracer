#include <fstream>
#include "FileHandler.h"
#include "Logging/Log.h"

namespace RayTracer {
    std::string FileHandler::ProducePPMImage() {
        std::string image{};

        image += "P3\n" + std::to_string(m_baseImageWidth) + ' ' + std::to_string(m_baseImageHeight) + "\n255\n";

        for (int row = 0; row < m_baseImageHeight; ++row) {
            LOG_INFO("Lines remaining: {0}", m_baseImageHeight - row);

            auto rowAsDouble = static_cast<double>(row);

            for (int column = 0; column < m_baseImageWidth; ++column) {
                auto columnAsDouble = static_cast<double>(column);

                double red = rowAsDouble / (m_baseImageWidth - 1);
                double green = columnAsDouble / (m_baseImageHeight - 1);
                double blue = 0;

                int redAsRGB = static_cast<int>(m_rgbConversionValue * red);
                int greenAsRGB = static_cast<int>(m_rgbConversionValue * green);
                int blueAsRGB = static_cast<int>(m_rgbConversionValue * blue);

                image += std::to_string(redAsRGB) + ' ' + std::to_string(greenAsRGB) + ' ' + std::to_string(blueAsRGB) +
                         '\n';
            }
        }

        return image;
    }

    void FileHandler::WriteToFile(const std::string& contents) {
        std::ofstream outputStream{m_fileName, std::ios::out | std::ios::trunc};

        if (!outputStream.is_open()) {
            LOG_CRITICAL("Failed to open stream to write to file {0}", m_fileName);
            assert(false);
        }

        outputStream << contents << std::endl;
        outputStream.close();
    }
}
