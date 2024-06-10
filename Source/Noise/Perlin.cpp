#include "Perlin.h"

namespace RayTracer
{
    Perlin::Perlin()
    {
        m_randomFloat = new float[m_pointCount];

        for (int index = 0; index < m_pointCount; ++index)
        {
            m_randomFloat[index] = Utilities::RandomFloat();
        }

        m_permanentX = PerlinGeneratePermanent();
        m_permanentY = PerlinGeneratePermanent();
        m_permanentZ = PerlinGeneratePermanent();
    }

    Perlin::~Perlin()
    {
        delete[] m_randomFloat;
        delete[] m_permanentX;
        delete[] m_permanentY;
        delete[] m_permanentZ;
    }

    float Perlin::Noise(const Point3& point) const
    {
        const int i = static_cast<int>(4 * point.X()) & 255;
        const int j = static_cast<int>(4 * point.Y()) & 255;
        const int k = static_cast<int>(4 * point.Z()) & 255;

        return m_randomFloat[m_permanentX[i] ^ m_permanentY[j] ^ m_permanentZ[k]];
    }

    int* Perlin::PerlinGeneratePermanent()
    {
        const auto point = new int[m_pointCount];

        for (int index = 0; index < m_pointCount; ++index)
        {
            point[index] = index;
        }

        Permute(point, m_pointCount);

        return point;
    }

    void Perlin::Permute(int* point, const int number)
    {
        for (int index = number - 1; index > 0; index--)
        {
            const int target = Utilities::RandomInt(0, index);
            const int temp = point[index];
            point[index] = point[target];
            point[target] = temp;
        }
    }
}
