/*
 * InfiniteScript
 *
 * Copyright (c) 2026 InfiniteScript Project.
 * All rights reserved.
 *
 * See LICENSE for licensing terms.
 */
#include <algorithm>

#include "Interpolation.h"

namespace InfiniteScript
{
    float interpolate(
        float start,
        float end,
        float t
    )
    {
        t = std::clamp(t, 0.0f, 1.0f);

        return start + (end - start) * t;
    }

    Vector2 interpolate(
        const Vector2& start,
        const Vector2& end,
        float t
    )
    {
        t = std::clamp(t, 0.0f, 1.0f);

        return Vector2(
            interpolate(start.x, end.x, t),
            interpolate(start.y, end.y, t)
        );
    }

    Vector3 interpolate(
        const Vector3& start,
        const Vector3& end,
        float t
    )
    {
        t = std::clamp(t, 0.0f, 1.0f);

        return Vector3(
            interpolate(start.x, end.x, t),
            interpolate(start.y, end.y, t),
            interpolate(start.z, end.z, t)
        );
    }

    Color interpolate(
        const Color& start,
        const Color& end,
        float t
    )
    {
        t = std::clamp(t, 0.0f, 1.0f);

        return Color(
            interpolate(start.r, end.r, t),
            interpolate(start.g, end.g, t),
            interpolate(start.b, end.b, t),
            interpolate(start.a, end.a, t)
        );
    }
}
