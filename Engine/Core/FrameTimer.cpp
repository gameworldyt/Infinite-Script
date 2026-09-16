/*
 * InfiniteScript
 *
 * Copyright (c) 2026 InfiniteScript Project.
 * All rights reserved.
 *
 * See LICENSE for licensing terms.
 */
#include <algorithm>

#include "FrameTimer.h"

namespace InfiniteScript
{
    FrameTimer::FrameTimer()
    {
        reset();
    }


    float FrameTimer::deltaTime()
    {
        Clock::time_point currentTime =
            Clock::now();

        std::chrono::duration<float, std::milli> elapsed =
            currentTime - lastTime;

        lastTime = currentTime;

        float delta =
            elapsed.count();

        delta =
            std::clamp(
                delta,
                0.0f,
                maximumDeltaTime
            );

        return delta;
    }


    void FrameTimer::setMaximumDeltaTime(
        float milliseconds
    )
    {
        maximumDeltaTime =
            std::max(
                1.0f,
                milliseconds
            );
    }


    void FrameTimer::reset()
    {
        lastTime = Clock::now();
    }
}

