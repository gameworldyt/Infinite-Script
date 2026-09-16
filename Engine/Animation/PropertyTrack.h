/*
 * InfiniteScript
 *
 * Copyright (c) 2026 InfiniteScript Project.
 * All rights reserved.
 *
 * See LICENSE for licensing terms.
 */
#pragma once

#include "Interpolation.h"

namespace InfiniteScript
{
    class PropertyTrack
    {
    public:
        enum class Type
        {
            Float,
            Vector2,
            Vector3,
            Color
        };

    private:
        Type type;

        float* floatTarget;
        Vector2* vector2Target;
        Vector3* vector3Target;
        Color* colorTarget;

        float floatStart;
        float floatEnd;

        Vector2 vector2Start;
        Vector2 vector2End;

        Vector3 vector3Start;
        Vector3 vector3End;

        Color colorStart;
        Color colorEnd;

    public:
        PropertyTrack(
            float* target,
            float start,
            float end
        );

        PropertyTrack(
            Vector2* target,
            const Vector2& start,
            const Vector2& end
        );

        PropertyTrack(
            Vector3* target,
            const Vector3& start,
            const Vector3& end
        );

        PropertyTrack(
            Color* target,
            const Color& start,
            const Color& end
        );

        void update(
            float progress
        );

        Type getType() const;
    };
}
