#ifndef BVH_H
#define BVH_H

namespace RayTracer
{
    class BVHNode final : public IHittable
    {
    public:
        explicit BVHNode(HittableVector vector);
        BVHNode(std::vector<std::shared_ptr<IHittable>>& objects, size_t start, size_t end);

        bool Hit(const Ray& ray, Interval interval, HitResult& result) const override;
        [[nodiscard]] AABB BoundingBox() const override;

        static bool BoxCompare(const std::shared_ptr<IHittable>& first, const std::shared_ptr<IHittable>& second, int axisIndex);
        static bool BoxXCompare(const std::shared_ptr<IHittable>& first, const std::shared_ptr<IHittable>& second);
        static bool BoxYCompare(const std::shared_ptr<IHittable>& first, const std::shared_ptr<IHittable>& second);
        static bool BoxZCompare(const std::shared_ptr<IHittable>& first, const std::shared_ptr<IHittable>& second);

    private:
        std::shared_ptr<IHittable> m_left;
        std::shared_ptr<IHittable> m_right;
        AABB m_boundingBox;
    };
} // RayTracer

#endif // BVH_H
