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
        float* m_randomFloat;
        int* m_permanentX;
        int* m_permanentY;
        int* m_permanentZ;

        static int* PerlinGeneratePermanent();
        static void Permute(int* point, int number);
    };
}

#endif // PERLIN_H
