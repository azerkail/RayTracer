#include "Camera.h"

namespace RayTracer {
    void Camera::Initialise(int imageWidth, int imageHeight) {
        auto imageWidthAsFloat = static_cast<float>(imageWidth);
        auto imageHeightAsFloat = static_cast<float>(imageHeight);
        float viewportHeight = 2.0;
        float viewportWidth = viewportHeight * static_cast<float>(imageWidthAsFloat / imageHeightAsFloat);

        Vector3 viewportU{viewportWidth, 0, 0};
        Vector3 viewportV{0, -viewportHeight, 0};

        m_pixelDeltaU = viewportU / imageWidthAsFloat;
        m_pixelDeltaV = viewportV / imageHeightAsFloat;

        Vector3 viewportUpperLeft = m_center - Vector3{0, 0, FocalLength()} - viewportU / 2 - viewportV / 2;
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
