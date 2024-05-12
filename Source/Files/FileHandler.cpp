#include <fstream>
#include "FileHandler.h"
#include "Logging/Log.h"

namespace RayTracer {
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
