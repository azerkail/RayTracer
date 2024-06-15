#ifndef TRANSLATE_H
#define TRANSLATE_H

namespace RayTracer
{
    class Translate final : public IHittable
    {
    public:
        Translate(std::shared_ptr<IHittable> object, const Vector3& offset);

        bool Hit(const Ray& ray, Interval interval, HitResult& result) const override;
        [[nodiscard]] AABB BoundingBox() const override;

    private:
        std::shared_ptr<IHittable> m_object;
        Vector3 m_offset;
        AABB m_boundingBox;
    };
}

#endif
