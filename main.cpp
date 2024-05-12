#include "Logging/Log.h"
#include "Engine.h"
#include "Renderers/Terminal.h"

int main() {
    RayTracer::Log::Initialise();

    RayTracer::Terminal terminal{};
    RayTracer::Engine rayTracer{terminal};

    rayTracer.Trace();
    rayTracer.Finish();

    return 0;
}
