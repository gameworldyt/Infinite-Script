/*
 * InfiniteScript
 *
 * Copyright (c) 2026 InfiniteScript Project.
 * All rights reserved.
 *
 * See LICENSE for licensing terms.
 */
#include "AnimationProperty.h"

namespace InfiniteScript
{
    AnimationProperty::AnimationProperty(
        float* targetValue,
        float start,
        float end,
        float durationMilliseconds,
        Easing easing
    )
        : animation(
              start,
              end,
              durationMilliseconds,
              easing
          ),
          target(targetValue)
    {
        if (target != nullptr)
        {
            *target = start;
        }
    }


    void AnimationProperty::update(
        float deltaTime
    )
    {
        animation.update(deltaTime);

        if (target != nullptr)
        {
            *target =
                animation.getValue();
        }
    }


    void AnimationProperty::pause()
    {
        animation.pause();
    }


    void AnimationProperty::resume()
    {
        animation.resume();
    }


    void AnimationProperty::cancel()
    {
        animation.cancel();
    }


    bool AnimationProperty::isFinished() const
    {
        return animation.isFinished();
    }


    float AnimationProperty::getValue() const
    {
        return animation.getValue();
    }
}


