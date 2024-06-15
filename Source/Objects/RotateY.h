#ifndef ROTATEY_H
#define ROTATEY_H

namespace RayTracer
{
    class RotateY final : public IHittable
    {
    public:
        RotateY(std::shared_ptr<IHittable> object, float angle);

        bool Hit(const Ray& ray, Interval interval, HitResult& result) const override;
        [[nodiscard]] AABB BoundingBox() const override;

    private:
        std::shared_ptr<IHittable> m_object;
        float m_sinTheta;
        float m_cosTheta;
        AABB m_boundingBox;
    };
}

#endif
