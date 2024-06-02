#ifndef TEXTURE_H
#define TEXTURE_H

#include "Maths/Vector3.h"

namespace RayTracer
{
    class ITexture
    {
    public:
        virtual ~ITexture() = default;
        [[nodiscard]] virtual Color Value(float u, float v, const Point3& result) const = 0;
    };
}

#endif // TEXTURE_H
