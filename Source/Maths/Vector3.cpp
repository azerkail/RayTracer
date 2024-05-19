#include <cmath>
#include "Vector3.h"

namespace RayTracer {
    Vector3::Vector3() : m_values{0, 0, 0} {}

    Vector3::Vector3(float x, float y, float z) : m_values{x, y, z} {}

    float Vector3::X() const { return m_values[0]; }

    float Vector3::Y() const { return m_values[1]; }

    float Vector3::Z() const { return m_values[2]; }

    Vector3 Vector3::operator-() const {
        return {-m_values[0], -m_values[1], -m_values[2]};
    }

    Vector3& Vector3::operator+=(const Vector3& other) {
        m_values[0] += other.m_values[0];
        m_values[1] += other.m_values[1];
        m_values[2] += other.m_values[2];
        return *this;
    }

    Vector3& Vector3::operator*=(float value) {
        m_values[0] *= value;
        m_values[1] *= value;
        m_values[2] *= value;
        return *this;
    }

    Vector3& Vector3::operator/=(float value) {
        return *this *= 1 / value;
    }

    float Vector3::operator[](int index) const {
        return m_values[index];
    }

    float& Vector3::operator[](int index) {
        return m_values[index];
    }

    float Vector3::Length() const {
        return std::sqrt(LengthSquared());
    }

    float Vector3::LengthSquared() const {
        return m_values[0] * m_values[0] + m_values[1] * m_values[1] + m_values[2] * m_values[2];
    }

    bool Vector3::NearZero() const {
        auto nearZero = 1e-8f;
        return std::fabs(m_values[0]) < nearZero && std::fabs(m_values[1]) < nearZero && std::fabs(m_values[2]) < 2;
    }

    std::ostream& operator<<(std::ostream& out, const Vector3& vector) {
        return out << vector.X() << ' ' << vector.Y() << ' ' << vector.Z();
    }

    Vector3 operator+(const Vector3& u, const Vector3& v) {
        return {u.X() + v.X(), u.Y() + v.Y(), u.Z() + v.Z()};
    }

    Vector3 operator-(const Vector3& u, const Vector3& v) {
        return {u.X() - v.X(), u.Y() - v.Y(), u.Z() - v.Z()};
    }

    Vector3 operator*(const Vector3& u, const Vector3& v) {
        return {u.X() * v.X(), u.Y() * v.Y(), u.Z() * v.Z()};
    }

    Vector3 operator*(const Vector3& vector, float value) {
        return {vector.X() * value, vector.Y() * value, vector.Z() * value};
    }

    Vector3 operator*(float value, const Vector3& vector) {
        return vector * value;
    }

    Vector3 operator/(const Vector3& vector, float value) {
        return vector * (1 / value);
    }

    float Dot(const Vector3& u, const Vector3& v) {
        return u.X() * v.X() + u.Y() * v.Y() + u.Z() * v.Z();
    }

    Vector3 Cross(const Vector3& u, const Vector3& v) {
        return {
                u.Y() * v.Z() - u.Z() * v.Y(),
                u.Z() * v.X() - u.X() * v.Z(),
                u.X() * v.Y() - u.Y() * v.X()
        };
    }

    Vector3 UnitVector(const Vector3& vector) {
        return vector / vector.Length();
    }

    Vector3 Random() {
        return {Utilities::RandomFloat(), Utilities::RandomFloat(), Utilities::RandomFloat()};
    }

    Vector3 Random(float min, float max) {
        return {Utilities::RandomFloat(min, max), Utilities::RandomFloat(min, max), Utilities::RandomFloat(min, max)};
    }

    Vector3 RandomUnitSphere() {
        while (true) {
            auto point = Random(-1, 1);
            if (point.LengthSquared() < 1) {
                return point;
            }
        }
    }

    Vector3 RandomUnitVector() {
        return UnitVector(RandomUnitSphere());
    }

    Vector3 RandomOnHemisphere(const Vector3& normal) {
        auto unitSphere = RandomUnitVector();

        if (Dot(unitSphere, normal) > 0.0f) {
            return unitSphere;
        }

        return -unitSphere;
    }

    Vector3 Reflect(const Vector3& vector, const Vector3& normal) {
        return vector - 2 * Dot(vector, normal) * normal;
    }

    Vector3 Refract(const Vector3& uv, const Vector3& normal, float etaIOverEtaT) {
        float cosTheta = std::fmin(Dot(-uv, normal), 1.0f);
        Vector3 rOutPerpendicular = etaIOverEtaT * (uv + cosTheta * normal);
        Vector3 rOutParallel = -std::sqrt(std::fabs(1.0f - rOutPerpendicular.LengthSquared())) * normal;
        return rOutPerpendicular + rOutParallel;
    }
}
