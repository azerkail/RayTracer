#include "FileHandler.h"
#include "Logging/Log.h"

int main() {
    RayTracer::Log::Initialise();

    const std::string& image = RayTracer::FileHandler::ProducePPMImage();
    LOG_INFO(image);
    RayTracer::FileHandler::WriteToFile(image);

    return 0;
}
