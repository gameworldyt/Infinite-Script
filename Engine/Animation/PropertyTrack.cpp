/*
 * InfiniteScript
 *
 * Copyright (c) 2026 InfiniteScript Project.
 * All rights reserved.
 *
 * See LICENSE for licensing terms.
 */
#include "PropertyTrack.h"

namespace InfiniteScript
{
    PropertyTrack::PropertyTrack(
        float* target,
        float start,
        float end
    )
        : type(Type::Float),
          floatTarget(target),
          vector2Target(nullptr),
          vector3Target(nullptr),
          colorTarget(nullptr),
          floatStart(start),
          floatEnd(end)
    {
        if (floatTarget != nullptr)
        {
            *floatTarget = start;
        }
    }

    PropertyTrack::PropertyTrack(
        Vector2* target,
        const Vector2& start,
        const Vector2& end
    )
        : type(Type::Vector2),
          floatTarget(nullptr),
          vector2Target(target),
          vector3Target(nullptr),
          colorTarget(nullptr),
          vector2Start(start),
          vector2End(end)
    {
        if (vector2Target != nullptr)
        {
            *vector2Target = start;
        }
    }

    PropertyTrack::PropertyTrack(
        Vector3* target,
        const Vector3& start,
        const Vector3& end
    )
        : type(Type::Vector3),
          floatTarget(nullptr),
          vector2Target(nullptr),
          vector3Target(target),
          colorTarget(nullptr),
          vector3Start(start),
          vector3End(end)
    {
        if (vector3Target != nullptr)
        {
            *vector3Target = start;
        }
    }

    PropertyTrack::PropertyTrack(
        Color* target,
        const Color& start,
        const Color& end
    )
        : type(Type::Color),
          floatTarget(nullptr),
          vector2Target(nullptr),
          vector3Target(nullptr),
          colorTarget(target),
          colorStart(start),
          colorEnd(end)
    {
        if (colorTarget != nullptr)
        {
            *colorTarget = start;
        }
    }

    void PropertyTrack::update(
        float progress
    )
    {
        switch (type)
        {
            case Type::Float:
                if (floatTarget != nullptr)
                {
                    *floatTarget =
                        interpolate(
                            floatStart,
                            floatEnd,
                            progress
                        );
                }
                break;

            case Type::Vector2:
                if (vector2Target != nullptr)
                {
                    *vector2Target =
                        interpolate(
                            vector2Start,
                            vector2End,
                            progress
                        );
                }
                break;

            case Type::Vector3:
                if (vector3Target != nullptr)
                {
                    *vector3Target =
                        interpolate(
                            vector3Start,
                            vector3End,
                            progress
                        );
                }
                break;

            case Type::Color:
                if (colorTarget != nullptr)
                {
                    *colorTarget =
                        interpolate(
                            colorStart,
                            colorEnd,
                            progress
                        );
                }
                break;
        }
    }

    PropertyTrack::Type PropertyTrack::getType() const
    {
        return type;
    }
}
