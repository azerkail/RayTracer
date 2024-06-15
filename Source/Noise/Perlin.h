#ifndef PERLIN_H
#define PERLIN_H

namespace RayTracer
{
    class Perlin
    {
    public:
        Perlin();
        ~Perlin();

        [[nodiscard]] float Noise(const Point3& point) const;

    private:
        static constexpr int m_pointCount = 256;
        Vector3* m_randomVectors;
        int* m_permanentX;
        int* m_permanentY;
        int* m_permanentZ;

        static int* PerlinGeneratePermanent();
        static void Permute(int* point, int number);
        static float TrilinearInterpolation(float c[2][2][2], float u, float v, float w);
        static float PerlinInterpolation(const Vector3 c[2][2][2], float u, float v, float w);
    };
}

#endif // PERLIN_H
