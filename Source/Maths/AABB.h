#ifndef AABB_H
#define AABB_H

namespace RayTracer
{
    class AABB
    {
    public:
        AABB() = default;
        AABB(const Interval& x, const Interval& y, const Interval& z);
        AABB(const Point3& first, const Point3& second);
        AABB(const AABB& first, const AABB& second);

        [[nodiscard]] const Interval& AxisInterval(int number) const;
        [[nodiscard]] bool Hit(const Ray& ray, Interval rayInterval) const;

    private:
        Interval m_x, m_y, m_z;
    };
}

#endif // AABB_H