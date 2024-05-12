#include <iostream>
#include "FileHandler.h"
#include "Logging/Log.h"

int main() {
    RayTracer::Log::Initialise();
    const std::string& image = RayTracer::FileHandler::ReadFile();

    std::cout << image << std::endl;
    return 0;
}
