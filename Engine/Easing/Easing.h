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
    enum class Easing
    {
        Linear,

        EaseIn,
        EaseOut,
        EaseInOut,

        EaseInCubic,
        EaseOutCubic,
        EaseInOutCubic,

        EaseInQuart,
        EaseOutQuart,
        EaseInOutQuart,

        EaseInQuint,
        EaseOutQuint,
        EaseInOutQuint,

        EaseInExpo,
        EaseOutExpo,
        EaseInOutExpo,

        EaseInCirc,
        EaseOutCirc,
        EaseInOutCirc,

        EaseInBack,
        EaseOutBack,
        EaseInOutBack,

        EaseInElastic,
        EaseOutElastic,
        EaseInOutElastic,

        EaseInBounce,
        EaseOutBounce,
        EaseInOutBounce
    };

    float applyEasing(
        float t,
        Easing easing
    );
}

