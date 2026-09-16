/*
 * InfiniteScript
 *
 * Copyright (c) 2026 InfiniteScript Project.
 * All rights reserved.
 *
 * See LICENSE for licensing terms.
 */
#pragma once

#include <chrono>

namespace InfiniteScript
{
    class FrameTimer
    {
    private:
        using Clock = std::chrono::steady_clock;

        Clock::time_point lastTime;

        float maximumDeltaTime = 100.0f;

    public:

        FrameTimer();

        float deltaTime();

        void setMaximumDeltaTime(
            float milliseconds
        );

        void reset();
    };
}

