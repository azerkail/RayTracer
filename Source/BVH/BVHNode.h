#ifndef BVH_H
#define BVH_H

namespace RayTracer
{
    class BVHNode final : public Hittable
    {
    public:
        explicit BVHNode(HittableVector vector);
        BVHNode(std::vector<std::shared_ptr<Hittable>>& objects, size_t start, size_t end);

        bool Hit(const Ray& ray, Interval interval, HitResult& result) const override;
        [[nodiscard]] AABB BoundingBox() const override;

        static bool BoxCompare(const std::shared_ptr<Hittable>& first, const std::shared_ptr<Hittable>& second, int axisIndex);
        static bool BoxXCompare(const std::shared_ptr<Hittable>& first, const std::shared_ptr<Hittable>& second);
        static bool BoxYCompare(const std::shared_ptr<Hittable>& first, const std::shared_ptr<Hittable>& second);
        static bool BoxZCompare(const std::shared_ptr<Hittable>& first, const std::shared_ptr<Hittable>& second);

    private:
        std::shared_ptr<Hittable> m_left;
        std::shared_ptr<Hittable> m_right;
        AABB m_boundingBox;
    };
} // RayTracer

#endif // BVH_H
