/*
 * InfiniteScript
 *
 * Copyright (c) 2026 InfiniteScript Project.
 * All rights reserved.
 *
 * See LICENSE for licensing terms.
 */
#pragma once

#include "..\Easing\Easing.h"

namespace InfiniteScript
{
    struct Keyframe
    {
        float time;

        float value;

        Easing easing;

        Keyframe(
            float timeValue,
            float valueValue,
            Easing easingValue =
                Easing::EaseOut
        )
            : time(timeValue),
              value(valueValue),
              easing(easingValue)
        {
        }
    };
}

