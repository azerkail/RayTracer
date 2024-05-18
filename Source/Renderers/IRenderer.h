#ifndef RAYTRACER_IRENDERER_H
#define RAYTRACER_IRENDERER_H

namespace RayTracer {

    class IRenderer {
    public:
        virtual ~IRenderer() = default;

        virtual void Initialise(int imageWidth, int imageHeight) = 0;
        virtual void Render(const Color& vector3) = 0;
        virtual void Terminate() const = 0;
    };

}

#endif //RAYTRACER_IRENDERER_H
