/*
 * InfiniteScript
 *
 * Copyright (c) 2026 InfiniteScript Project.
 * All rights reserved.
 *
 * See LICENSE for licensing terms.
 */
#pragma once

#include "..\Animation\Animation.h"

namespace InfiniteScript
{
    class AnimationProperty
    {
    private:
        Animation animation;

        float* target;

    public:
        AnimationProperty(
            float* targetValue,
            float start,
            float end,
            float durationMilliseconds,
            Easing easing =
                Easing::EaseOut
        );

        void update(float deltaTime);

        void pause();

        void resume();

        void cancel();

        bool isFinished() const;

        float getValue() const;
    };
}

