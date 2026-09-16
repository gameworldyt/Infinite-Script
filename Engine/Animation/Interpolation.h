/*
 * InfiniteScript
 *
 * Copyright (c) 2026 InfiniteScript Project.
 * All rights reserved.
 *
 * See LICENSE for licensing terms.
 */
#pragma once

#include "..\Math\Vector2.h"
#include "..\Math\Vector3.h"
#include "..\Math\Color.h"

namespace InfiniteScript
{
    float interpolate(
        float start,
        float end,
        float t
    );

    Vector2 interpolate(
        const Vector2& start,
        const Vector2& end,
        float t
    );

    Vector3 interpolate(
        const Vector3& start,
        const Vector3& end,
        float t
    );

    Color interpolate(
        const Color& start,
        const Color& end,
        float t
    );
}
