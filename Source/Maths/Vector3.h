#ifndef RAYTRACER_VECTOR3_H
#define RAYTRACER_VECTOR3_H

#include <ostream>

namespace RayTracer {

    class Vector3 {
    public:
        Vector3();
        Vector3(float x, float y, float z);

        [[nodiscard]] float X() const;
        [[nodiscard]] float Y() const;
        [[nodiscard]] float Z() const;

        Vector3 operator-() const;
        Vector3& operator+=(const Vector3& other);
        Vector3& operator*=(float value);
        Vector3& operator/=(float value);
        float operator[](int index) const;
        float& operator[](int index);
        [[nodiscard]] float Length() const;
        [[nodiscard]] float LengthSquared() const;
        [[nodiscard]] bool NearZero() const;
    private:
        float m_values[3];
    };

    // Alias so a vector can be used as point for code clarity.
    using Point3 = Vector3;
    using Color = Vector3;

    std::ostream& operator<<(std::ostream& out, const Vector3& vector);
    Vector3 operator+(const Vector3& u, const Vector3& v);
    Vector3 operator-(const Vector3& u, const Vector3& v);
    Vector3 operator*(const Vector3& u, const Vector3& v);
    Vector3 operator*(const Vector3& vector, float value);
    Vector3 operator*(float value, const Vector3& vector);
    Vector3 operator/(const Vector3& vector, float value);

    float Dot(const Vector3& u, const Vector3& v);
    Vector3 Cross(const Vector3& u, const Vector3& v);
    Vector3 UnitVector(const Vector3& vector);
    Vector3 Random();
    Vector3 Random(float min, float max);
    Vector3 RandomInUnitSphere();
    Vector3 RandomInUnitVector();
    Vector3 RandomInUnitDisk();
    Vector3 RandomOnHemisphere(const Vector3& normal);
    Vector3 Reflect(const Vector3& vector, const Vector3& normal);
    Vector3 Refract(const Vector3& uv, const Vector3& normal, float etaIOverEtaT);

}

#endif //RAYTRACER_VECTOR3_H
