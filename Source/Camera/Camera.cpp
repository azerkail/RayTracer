#include "Camera.h"

namespace RayTracer {
    Camera::Camera(float imageWidth, float imageHeight) {
        float viewportHeight = 2.0;
        float viewportWidth = viewportHeight * static_cast<float>(imageWidth / imageHeight);
        m_center = Point3{};

        Color viewportU = {viewportWidth, 0, 0};
        Color viewportV = {0, -viewportHeight, 0};

        m_pixelDeltaU = viewportU / imageWidth;
        m_pixelDeltaV = viewportV / imageHeight;

        Color viewportUpperLeft = m_center - Color{0, 0, FocalLength()} - viewportU / 2 - viewportV / 2;
        m_pixelOrigin = viewportUpperLeft + 0.5 * (m_pixelDeltaU + m_pixelDeltaV);
    }

    float Camera::FocalLength() {
        return 1.0;
    }

    Point3 Camera::Center() const {
        return m_center;
    }

    Point3 Camera::PixelOrigin() const {
        return m_pixelOrigin;
    }

    Color Camera::PixelDeltaU() const {
        return m_pixelDeltaU;
    }

    Color Camera::PixelDeltaV() const {
        return m_pixelDeltaV;
    }
}
