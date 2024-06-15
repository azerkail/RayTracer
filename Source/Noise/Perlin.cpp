#include "Perlin.h"

namespace RayTracer
{
    Perlin::Perlin()
    {
        m_randomVectors = new Vector3[m_pointCount];

        for (int index = 0; index < m_pointCount; ++index)
        {
            m_randomVectors[index] = UnitVector(Random(-1, 1));
        }

        m_permanentX = PerlinGeneratePermanent();
        m_permanentY = PerlinGeneratePermanent();
        m_permanentZ = PerlinGeneratePermanent();
    }

    Perlin::~Perlin()
    {
        delete[] m_randomVectors;
        delete[] m_permanentX;
        delete[] m_permanentY;
        delete[] m_permanentZ;
    }

    float Perlin::Noise(const Point3& point) const
    {
        const float u = point.X() - std::floor(point.X());
        const float v = point.Y() - std::floor(point.Y());
        const float w = point.Z() - std::floor(point.Z());

        const auto i = static_cast<int>(std::floor(point.X()));
        const auto j = static_cast<int>(std::floor(point.Y()));
        const auto k = static_cast<int>(std::floor(point.Z()));

        Vector3 c[2][2][2];

        for (int di = 0; di < 2; ++di)
        {
            for (int dj = 0; dj < 2; ++dj)
            {
                for (int dk = 0; dk < 2; ++dk)
                {
                    c[di][dj][dk] = m_randomVectors[
                        m_permanentX[(i + di) & 255] ^
                        m_permanentY[(j + dj) & 255] ^
                        m_permanentZ[(k + dk) & 255]
                    ];
                }
            }
        }

        return PerlinInterpolation(c, u, v, w);
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

    float Perlin::TrilinearInterpolation(float c[2][2][2], const float u, const float v, const float w)
    {
        float accumulator = 0.0f;

        for (int i = 0; i < 2; ++i)
        {
            const auto iAsFloat = static_cast<float>(i);

            for (int j = 0; j < 2; ++j)
            {
                const auto jAsFloat = static_cast<float>(j);

                for (int k = 0; k < 2; ++k)
                {
                    const auto kAsFloat = static_cast<float>(k);

                    accumulator += (iAsFloat * u + (1 - iAsFloat) * (1 - u)) *
                        (jAsFloat * v + (1 - jAsFloat) * (1 - v)) *
                        (kAsFloat * w + (1 - kAsFloat) * (1 - w)) *
                        c[i][j][k];
                }
            }
        }

        return accumulator;
    }

    float Perlin::PerlinInterpolation(const Vector3 c[2][2][2], const float u, const float v, const float w)
    {
        const float uu = u * u * (3 - 2 * u);
        const float vv = v * v * (3 - 2 * v);
        const float ww = w * w * (3 - 2 * w);
        float accumulator = 0.0f;

        for (int i = 0; i < 2; ++i)
        {
            const auto iAsFloat = static_cast<float>(i);

            for (int j = 0; j < 2; ++j)
            {
                const auto jAsFloat = static_cast<float>(j);

                for (int k = 0; k < 2; ++k)
                {
                    const auto kAsFloat = static_cast<float>(k);
                    const Vector3 weightV{u - iAsFloat, v - jAsFloat, w - kAsFloat};

                    accumulator += (iAsFloat * uu + (1 - iAsFloat) * (1 - uu)) *
                        (jAsFloat * vv + (1 - jAsFloat) * (1 - vv)) *
                        (kAsFloat * ww + (1 - kAsFloat) * (1 - ww)) *
                        Dot(c[i][j][k], weightV);
                }
            }
        }

        return accumulator;
    }

    float Perlin::Turbulance(const Vector3& point, const int depth) const
    {
        float accumulator = 0.0f;
        float weight = 1.0f;
        Vector3 temporaryPoint = point;

        for (int index = 0; index < depth; ++index)
        {
            accumulator += weight * Noise(temporaryPoint);
            weight *= 0.5f;
            temporaryPoint *= 2;
        }

        return std::fabs(accumulator);
    }
}
