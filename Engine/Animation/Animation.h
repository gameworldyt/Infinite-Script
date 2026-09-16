/*
 * InfiniteScript
 *
 * Copyright (c) 2026 InfiniteScript Project.
 * All rights reserved.
 *
 * See LICENSE for licensing terms.
 */
#pragma once

#include <functional>

#include "..\Easing\Easing.h"

namespace InfiniteScript
{
    class Animation
    {
    private:
        float startValue;
        float endValue;

        float duration;
        float elapsed;

        float currentValue;
        float progress;

        Easing easing;

        bool finished;
        bool paused;
        bool cancelled;

        int repeatCount;
        int completedRepeats;

        std::function<void()> onComplete;
        std::function<void()> onUpdate;

    public:
        Animation(
            float start,
            float end,
            float durationMilliseconds,
            Easing easingType = Easing::EaseOut
        );

        void update(float deltaTime);

        void pause();

        void resume();

        void cancel();

        void reset();

        void reverse();

        void setRepeatCount(int count);

        void setOnComplete(
            std::function<void()> callback
        );

        void setOnUpdate(
            std::function<void()> callback
        );

        float getValue() const;

        float getProgress() const;

        float getDuration() const;

        bool isFinished() const;

        bool isPaused() const;

        bool isCancelled() const;

        bool isActive() const;
    };
}

