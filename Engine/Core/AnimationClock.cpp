/*
 * InfiniteScript
 *
 * Copyright (c) 2026 InfiniteScript Project.
 * All rights reserved.
 *
 * See LICENSE for licensing terms.
 */
#include <algorithm>

#include "AnimationClock.h"

namespace InfiniteScript
{
    AnimationClock::AnimationClock()
        : maximumDeltaTime(100.0f),
          started(false)
    {
        reset();
    }

    void AnimationClock::start()
    {
        lastTime = Clock::now();
        started = true;
    }

    float AnimationClock::tick()
    {
        if (!started)
        {
            start();
            return 0.0f;
        }

        Clock::time_point currentTime =
            Clock::now();

        std::chrono::duration<float, std::milli>
            elapsed =
                currentTime - lastTime;

        lastTime = currentTime;

        float delta =
            elapsed.count();

        delta = std::clamp(
            delta,
            0.0f,
            maximumDeltaTime
        );

        return delta;
    }

    void AnimationClock::reset()
    {
        lastTime = Clock::now();
        started = true;
    }

    void AnimationClock::setMaximumDeltaTime(
        float milliseconds
    )
    {
        maximumDeltaTime =
            std::max(
                1.0f,
                milliseconds
            );
    }

    float AnimationClock::getMaximumDeltaTime() const
    {
        return maximumDeltaTime;
    }
}

