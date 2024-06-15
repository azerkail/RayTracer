#ifndef RAYTRACER_CAMERA_H
#define RAYTRACER_CAMERA_H

#include "Renderers/IRenderer.h"

namespace RayTracer
{
    class Camera
    {
    public:
        explicit Camera(std::unique_ptr<IRenderer> renderer);

        float AspectRatio = 1.0;
        float VerticalFOV = 90;
        float DefocusAngle = 0;
        float FocusDistance = 10;
        int ImageWidth = 100;
        int SamplesPerPixel = 10;
        int MaxDepth = 10;
        Point3 LookFrom;
        Point3 LookAt{0, 0, -1};
        Vector3 Up{0, 1, 0};
        Color Background{0, 0, 0};

        void Render(const HittableVector& world);

    private:
        std::unique_ptr<IRenderer> m_renderer;
        int m_imageHeight = 0;
        float m_pixelSamplesScale = 0;
        Point3 m_center;
        Point3 m_pixelOrigin;
        Vector3 m_pixelDeltaU;
        Vector3 m_pixelDeltaV;
        Vector3 m_u, m_v, m_w; // Camera from basis vectors.
        Vector3 m_defocusDiskU;
        Vector3 m_defocusDiskV;

        void Initialise();
        [[nodiscard]] Ray GetRay(int column, int row) const;
        [[nodiscard]] Point3 DefocusDiskSample() const;

        static Vector3 SampleSquare();
        Color GetRayColor(const Ray& ray, int depth, const HittableVector& world);
    };
}

#endif //RAYTRACER_CAMERA_H
