#include <fstream>
#include "FileHandler.h"

namespace RayTracer {
    std::string FileHandler::ReadFile() {
        std::ifstream inputStream{m_fileName};

        if (!inputStream.is_open()) {
            return ProduceBasicImage();
        }

        std::string image{};
        std::string line{};

        while (std::getline(inputStream, line)) {
            image += line;
            image += '\n';
        }

        inputStream.close();
        return image;
    }

    std::string FileHandler::ProduceBasicImage() {
        std::ofstream outputStream{m_fileName, std::ios::out | std::ios::app | std::ios::trunc};

        // We are writing a new file here, so it must not already be open.
        if (outputStream.is_open()) {
            // TODO Log error.
            return {};
        }

        std::string image{};

        for (int row = 0; row < m_baseImageWidth; ++row) {
            auto rowAsDouble = static_cast<double>(row);

            for (int column = 0; column < m_baseImageHeight; ++column) {
                auto columnAsDouble = static_cast<double>(column);

                double red = rowAsDouble / (m_baseImageWidth - 1);
                double green = columnAsDouble / (m_baseImageHeight - 1);
                double blue = 0;

                int redAsRGB = static_cast<int>(m_rgbConversionValue * red);
                int greenAsRGB = static_cast<int>(m_rgbConversionValue * green);
                int blueAsRGB = static_cast<int>(m_rgbConversionValue * blue);

                image += std::to_string(redAsRGB + ' ' + greenAsRGB + ' ' + blueAsRGB + '\n');
            }
        }

        outputStream << image << std::endl;
        outputStream.close();
        return image;
    }
}
