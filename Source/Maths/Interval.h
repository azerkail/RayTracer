#ifndef RAYTRACER_INTERVAL_H
#define RAYTRACER_INTERVAL_H

namespace RayTracer {

    class Interval {
    public:
        Interval();
        Interval(float min, float max);

        [[nodiscard]] float GetMin() const;
        [[nodiscard]] float GetMax() const;

        [[nodiscard]] float Size() const;
        [[nodiscard]] bool Contains(float value) const;
        [[nodiscard]] bool Surrounds(float value) const;
    private:
        float m_min, m_max;
    };

}

#endif //RAYTRACER_INTERVAL_H
