/*
 * InfiniteScript
 *
 * Copyright (c) 2026 InfiniteScript Project.
 * All rights reserved.
 *
 * See LICENSE for licensing terms.
 */
#pragma once

namespace InfiniteScript
{
    struct Vector2
    {
        float x;
        float y;

        Vector2()
            : x(0.0f), y(0.0f)
        {
        }

        Vector2(float xValue, float yValue)
            : x(xValue), y(yValue)
        {
        }
    };
}

