#include "Logging/Log.h"
#include "Engine.h"

int main() {
    RayTracer::Log::Initialise();

    RayTracer::Engine rayTracer{};

    rayTracer.Initialise();
    rayTracer.Trace();
    rayTracer.Terminate();

    return 0;
}
