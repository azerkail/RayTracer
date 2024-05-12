#ifndef RAYTRACER_CAMERA_H
#define RAYTRACER_CAMERA_H

#include "Maths/Vector3.h"

namespace RayTracer {

    class Camera {
    public:
        Camera(int imageWidth, int imageHeight);

        [[nodiscard]] static float FocalLength() ;
        [[nodiscard]] Point3 Center() const;
        [[nodiscard]] Point3 PixelOrigin() const;
        [[nodiscard]] Color PixelDeltaU() const;
        [[nodiscard]] Color PixelDeltaV() const;

    private:
        Point3 m_center;
        Point3 m_pixelOrigin;
        Color m_pixelDeltaU;
        Color m_pixelDeltaV;
    };

}

#endif //RAYTRACER_CAMERA_H
