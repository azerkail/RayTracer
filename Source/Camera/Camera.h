#ifndef RAYTRACER_CAMERA_H
#define RAYTRACER_CAMERA_H

#include "Renderers/IRenderer.h"

namespace RayTracer {

    class Camera {
    public:
        explicit Camera(std::unique_ptr<IRenderer> renderer);

        float AspectRatio = 1.0;
        int ImageWidth = 100;
        int SamplesPerPixel = 10;
        int MaxDepth = 10;

        void Render(const HittableVector& world);

    private:
        std::unique_ptr<IRenderer> m_renderer;
        int m_imageHeight = 0;
        float m_pixelSamplesScale = 0;
        Point3 m_center;
        Point3 m_pixelOrigin;
        Vector3 m_pixelDeltaU;
        Vector3 m_pixelDeltaV;

        void Initialise();
        [[nodiscard]] Ray GetRay(int column, int row) const;

        static Vector3 SampleSquare();
        static Color GetRayColor(const Ray& ray, int depth, const HittableVector& world);
    };

}

#endif //RAYTRACER_CAMERA_H
