#include "BVHNode.h"

namespace RayTracer
{
    BVHNode::BVHNode(HittableVector& vector) : BVHNode(vector.GetObjects(), 0, vector.GetObjects().size())
    {
    }

    BVHNode::BVHNode(std::vector<std::shared_ptr<Hittable>>& objects, const size_t start, const size_t end)
    {
        const int axis = Utilities::RandomInt(0, 2);
        const auto comparer = axis == 0 ? BoxXCompare : axis == 1 ? BoxYCompare : BoxZCompare;
        const size_t objectSpan = end - start;

        if (objectSpan == 1)
        {
            m_left = m_right = objects[start];
        }
        else if (objectSpan == 2)
        {
            m_left = objects[start];
            m_right = objects[start + 1];
        }
        else
        {
            const auto startValid = static_cast<long long int>(start);
            const auto endValid = static_cast<long long int>(end);
            std::sort(objects.begin() + startValid, objects.begin() + endValid, comparer);
            auto mid = start + objectSpan / 2;

            m_left = std::make_shared<BVHNode>(objects, start, mid);
            m_right = std::make_shared<BVHNode>(objects, mid, end);
        }

        m_boundingBox = AABB{m_left->BoundingBox(), m_right->BoundingBox()};
    }

    bool BVHNode::Hit(const Ray& ray, const Interval interval, HitResult& result) const
    {
        if (!m_boundingBox.Hit(ray, interval))
        {
            return false;
        }

        if (m_left->Hit(ray, interval, result))
        {
            return true;
        }

        if (m_right->Hit(ray, Interval{interval.GetMin(), interval.GetMax()}, result))
        {
            return true;
        }

        return false;
    }

    AABB BVHNode::BoundingBox() const
    {
        return m_boundingBox;
    }

    bool BVHNode::BoxCompare(const std::shared_ptr<Hittable>& first, const std::shared_ptr<Hittable>& second,
                             const int axisIndex)
    {
        const auto firstAxisInterval = first->BoundingBox().AxisInterval(axisIndex);
        const auto secondAxisInterval = second->BoundingBox().AxisInterval(axisIndex);
        return firstAxisInterval.GetMin() < secondAxisInterval.GetMin();
    }

    bool BVHNode::BoxXCompare(const std::shared_ptr<Hittable>& first, const std::shared_ptr<Hittable>& second)
    {
        return BoxCompare(first, second, 0);
    }

    bool BVHNode::BoxYCompare(const std::shared_ptr<Hittable>& first, const std::shared_ptr<Hittable>& second)
    {
        return BoxCompare(first, second, 1);
    }

    bool BVHNode::BoxZCompare(const std::shared_ptr<Hittable>& first, const std::shared_ptr<Hittable>& second)
    {
        return BoxCompare(first, second, 2);
    }
} // RayTracer
