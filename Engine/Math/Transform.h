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

namespace InfiniteScript
{
    struct Transform
    {
        Vector3 position;

        Vector3 rotation;

        Vector3 scale;

        Transform()
            : position(0.0f, 0.0f, 0.0f),
              rotation(0.0f, 0.0f, 0.0f),
              scale(1.0f, 1.0f, 1.0f)
        {
        }
    };
}

