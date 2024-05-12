#include "Logging/Log.h"
#include "Engine.h"
#include "Renderers/FileRenderer.h"

int main() {
    RayTracer::Log::Initialise();

    RayTracer::FileRenderer fileRenderer{};
    RayTracer::Engine rayTracer{fileRenderer};

    rayTracer.Trace();
    rayTracer.Terminate();

    return 0;
}
