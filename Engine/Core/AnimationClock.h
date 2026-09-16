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
    class AnimationClock
    {
    private:
        using Clock = std::chrono::steady_clock;

        Clock::time_point lastTime;

        float maximumDeltaTime;

        bool started;

    public:
        AnimationClock();

        void start();

        float tick();

        void reset();

        void setMaximumDeltaTime(
            float milliseconds
        );

        float getMaximumDeltaTime() const;
    };
}

