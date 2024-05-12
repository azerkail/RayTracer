#include "Logging/Log.h"
#include "RayTracer.h"
#include "Renderers/Terminal.h"

int main() {
    RayTracer::Log::Initialise();

    RayTracer::Terminal terminal{};
    RayTracer::RayTracer rayTracer{terminal};

    rayTracer.Trace();
    rayTracer.Finish();

    return 0;
}
