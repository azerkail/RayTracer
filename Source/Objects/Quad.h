#ifndef QUADRILATERAL_H
#define QUADRILATERAL_H

namespace RayTracer
{
    class Quad final : public IHittable
    {
    public:
        Quad(const Point3& q, const Vector3& u, const Vector3& v, std::shared_ptr<IMaterial> material);

        void SetBoundingBox();
        static bool IsInterior(float a, float b, HitResult& result);

        bool Hit(const Ray& ray, Interval interval, HitResult& result) const override;
        [[nodiscard]] AABB BoundingBox() const override;

    private:
        Point3 m_q;
        Vector3 m_u, m_v;
        Vector3 m_normal;
        Vector3 m_w;
        std::shared_ptr<IMaterial> m_material;
        AABB m_boundingBox;
        float m_d;
    };
}

#endif
