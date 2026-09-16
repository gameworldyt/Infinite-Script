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
    struct Color
    {
        float r;
        float g;
        float b;
        float a;

        Color()
            : r(1.0f),
              g(1.0f),
              b(1.0f),
              a(1.0f)
        {
        }

        Color(
            float red,
            float green,
            float blue,
            float alpha = 1.0f
        )
            : r(red),
              g(green),
              b(blue),
              a(alpha)
        {
        }
    };
}

