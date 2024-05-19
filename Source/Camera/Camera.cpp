#include "Camera.h"

namespace RayTracer {
    Camera::Camera(std::unique_ptr<IRenderer> renderer) : m_renderer(std::move(renderer)) {}

    void Camera::Initialise() {
        // Make sure image height is always at least 1 pixel.
        m_imageHeight = static_cast<int>(static_cast<float>(ImageWidth) / AspectRatio);
        m_imageHeight = m_imageHeight < 1 ? 1 : m_imageHeight;

        auto imageWidthAsFloat = static_cast<float>(ImageWidth);
        auto imageHeightAsFloat = static_cast<float>(m_imageHeight);

        m_pixelSamplesScale = 1.0f / static_cast<float>(SamplesPerPixel);
        m_center = LookFrom;

        // Viewport dimensions.
        float theta = Utilities::DegreesToRadians(VerticalFOV);
        float height = std::tan(theta / 2);
        float viewportHeight = 2.0f * height * FocusDistance;
        float viewportWidth = viewportHeight * (imageWidthAsFloat / imageHeightAsFloat);

        // Calculate unit basis vectors for the camera coordinate frame.
        m_w = UnitVector(LookFrom - LookAt);
        m_u = UnitVector(Cross(Up, m_w));
        m_v = Cross(m_w, m_u);

        Vector3 viewportU = viewportWidth * m_u;
        Vector3 viewportV = viewportHeight * -m_v;

        m_pixelDeltaU = viewportU / imageWidthAsFloat;
        m_pixelDeltaV = viewportV / imageHeightAsFloat;

        Vector3 viewportUpperLeft = m_center - (FocusDistance * m_w) - viewportU / 2 - viewportV / 2;
        m_pixelOrigin = viewportUpperLeft + 0.5 * (m_pixelDeltaU + m_pixelDeltaV);

        float defocusRadius = FocusDistance * std::tan(Utilities::DegreesToRadians(DefocusAngle / 2));
        m_defocusDiskU = m_u * defocusRadius;
        m_defocusDiskV = m_v * defocusRadius;

        // Initialise renderers.
        m_renderer->Initialise(ImageWidth, m_imageHeight);
    }

    void Camera::Render(const HittableVector& world) {
        Initialise();

        for (int row = 0; row < m_imageHeight; ++row) {
            LOG_INFO("Lines remaining: {0}", m_imageHeight - row);

            for (int column = 0; column < ImageWidth; ++column) {
                Color pixelColor;

                for (int sample = 0; sample < SamplesPerPixel; ++sample) {
                    Ray ray = GetRay(column, row);
                    pixelColor += GetRayColor(ray, MaxDepth, world);
                }

                m_renderer->Render(m_pixelSamplesScale * pixelColor);
            }
        }

        m_renderer->Terminate();
    }

    Vector3 Camera::SampleSquare() {
        return Vector3{Utilities::RandomFloat() - 0.5f, Utilities::RandomFloat() - 0.5f, 0};
    }

    Ray Camera::GetRay(int column, int row) const {
        auto columnAsFloat = static_cast<float>(column);
        auto rowAsFloat = static_cast<float>(row);

        Vector3 offset = SampleSquare();
        Vector3 pixelSample = m_pixelOrigin
                              + ((columnAsFloat + offset.X()) * m_pixelDeltaU)
                              + ((rowAsFloat + offset.Y()) * m_pixelDeltaV);

        Vector3 rayOrigin = DefocusAngle <= 0 ? m_center : DefocusDiskSample();
        Vector3 rayDirection = pixelSample - rayOrigin;

        return Ray{rayOrigin, rayDirection};
    }

    Point3 Camera::DefocusDiskSample() const {
        auto point = RandomInUnitDisk();
        return m_center + (point[0] * m_defocusDiskU) + (point[1] * m_defocusDiskV);
    }

    Color Camera::GetRayColor(const Ray& ray, int depth, const HittableVector& world) { // NOLINT(*-no-recursion)
        if (depth <= 0) {
            return Color{};
        }

        HitResult result;

        if (world.Hit(ray, Interval{0.001f, Constants::Infinity}, result)) {
            Ray scattered;
            Color attenuation;

            if (result.Material->Scatter(ray, result, attenuation, scattered)) {
                return attenuation * GetRayColor(scattered, depth - 1, world);
            }

            return Color{};
        }

        Vector3 unitDirection = UnitVector(ray.Direction());
        float alpha = 0.5f * (unitDirection.Y() + 1.0f);

        return (1 - alpha) * Color{1, 1, 1} + alpha * Color{0.5f, 0.7f, 1};
    }
}
