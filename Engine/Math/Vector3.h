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
    struct Vector3
    {
        float x;
        float y;
        float z;

        Vector3()
            : x(0.0f),
              y(0.0f),
              z(0.0f)
        {
        }

        Vector3(
            float xValue,
            float yValue,
            float zValue
        )
            : x(xValue),
              y(yValue),
              z(zValue)
        {
        }
    };
}

