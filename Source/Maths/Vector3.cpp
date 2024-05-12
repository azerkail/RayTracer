#include <cmath>const Vector3&
#include "Vector3.h"

namespace RayTracer {
    Vector3::Vector3() : values{0, 0, 0} {}

    Vector3::Vector3(float x, float y, float z) : values{x, y, z} {}

    float Vector3::X() const { return values[0]; }

    float Vector3::Y() const { return values[1]; }

    float Vector3::Z() const { return values[2]; }

    Vector3 Vector3::operator-() const {
        return {-values[0], -values[1], -values[2]};
    }

    Vector3& Vector3::operator+=(const Vector3& other) {
        values[0] += other.values[0];
        values[1] += other.values[1];
        values[2] += other.values[2];
        return *this;
    }

    Vector3& Vector3::operator*=(float value) {
        values[0] *= value;
        values[1] *= value;
        values[2] *= value;
        return *this;
    }

    Vector3& Vector3::operator/=(float value) {
        return *this *= 1 / value;
    }

    float Vector3::operator[](int index) const {
        return values[index];
    }

    float& Vector3::operator[](int index) {
        return values[index];
    }

    float Vector3::Length() const {
        return std::sqrt(LengthSquared());
    }

    float Vector3::LengthSquared() const {
        return values[0] * values[0] + values[1] * values[1] + values[2] * values[2];
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

    Vector3 Unit(const Vector3& vector) {
        return vector / vector.Length();
    }
}
