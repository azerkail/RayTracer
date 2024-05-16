#include "Camera.h"
#include "Logging/Log.h"

namespace RayTracer {
    Camera::Camera(std::unique_ptr<RendererBase> renderer) : m_renderer(std::move(renderer)) {}

    void Camera::Initialise() {
        // Make sure image height is always at least 1 pixel.
        m_imageHeight = ImageWidth / static_cast<int>(AspectRatio);
        m_imageHeight = m_imageHeight < 1 ? 1 : m_imageHeight;

        auto imageWidthAsFloat = static_cast<float>(ImageWidth);
        auto imageHeightAsFloat = static_cast<float>(m_imageHeight);

        // Viewport dimensions.
        float focalLength = 1.0;
        float viewportHeight = 2.0;
        float viewportWidth = viewportHeight * (imageWidthAsFloat / imageHeightAsFloat);

        Vector3 viewportU{viewportWidth, 0, 0};
        Vector3 viewportV{0, -viewportHeight, 0};

        m_pixelDeltaU = viewportU / imageWidthAsFloat;
        m_pixelDeltaV = viewportV / imageHeightAsFloat;

        Vector3 viewportUpperLeft = m_center - Vector3{0, 0, focalLength} - viewportU / 2 - viewportV / 2;
        m_pixelOrigin = viewportUpperLeft + 0.5 * (m_pixelDeltaU + m_pixelDeltaV);

        // Initialise renderers.
        m_renderer->Initialise(ImageWidth, m_imageHeight);
    }

    void Camera::Render(const HittableVector& world) {
        Initialise();

        for (int row = 0; row < m_imageHeight; ++row) {
            LOG_INFO("Lines remaining: {0}", m_imageHeight - row);

            auto rowAsFloat = static_cast<float>(row);

            for (int column = 0; column < ImageWidth; ++column) {
                auto columnAsFloat = static_cast<float>(column);
                auto pixelCenter = m_pixelOrigin + (columnAsFloat * m_pixelDeltaU) + (rowAsFloat * m_pixelDeltaV);
                auto rayDirection = pixelCenter - m_center;

                Ray ray{m_center, rayDirection};
                Color color = GetRayColor(ray, world);

                m_renderer->Render(color);
            }
        }

        m_renderer->Terminate();
    }

    Color Camera::GetRayColor(const Ray& ray, const HittableVector& world) {
        HitResult result;

        if (world.Hit(ray, Interval{0, Constants::Infinity}, result)) {
            return 0.5 * (result.Normal + Color{1, 1, 1});
        }

        Vector3 unitDirection = UnitVector(ray.Direction());
        float alpha = 0.5f * (unitDirection.Y() + 1.0f);

        return (1 - alpha) * Color{1, 1, 1} + alpha * Color{0.5f, 0.7f, 1};
    }
}
