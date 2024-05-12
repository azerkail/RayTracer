#include <iostream>
#include "./Source/FileHandler.h"

int main() {
    const std::string& image = RayTracer::FileHandler::ReadFile();

    std::cout << image << std::endl;
    return 0;
}
