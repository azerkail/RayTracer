#ifndef RAYTRACER_INTERVAL_H
#define RAYTRACER_INTERVAL_H

namespace RayTracer
{
    class Interval
    {
    public:
        Interval();
        Interval(float min, float max);
        Interval(const Interval& first, const Interval& second);

        [[nodiscard]] float Min() const;
        [[nodiscard]] float Max() const;
        void SetMin(float min);
        void SetMax(float max);

        [[nodiscard]] float Size() const;
        [[nodiscard]] float Clamp(float value) const;
        [[nodiscard]] bool Contains(float value) const;
        [[nodiscard]] bool Surrounds(float value) const;
        [[nodiscard]] Interval Expand(float delta) const;

    private:
        float m_min, m_max;
    };

    Interval operator+(const Interval& interval, float displacement);
    Interval operator+(float displacement, const Interval& interval);
}

#endif // RAYTRACER_INTERVAL_H
