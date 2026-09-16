/*
 * InfiniteScript
 *
 * Copyright (c) 2026 InfiniteScript Project.
 * All rights reserved.
 *
 * See LICENSE for licensing terms.
 */
#include <algorithm>

#include "AnimationScheduler.h"

namespace InfiniteScript
{
    AnimationScheduler::AnimationScheduler()
        : paused(false)
    {
    }

    void AnimationScheduler::add(
        Animation* animation
    )
    {
        if (animation == nullptr)
            return;

        animations.push_back(animation);
    }

    void AnimationScheduler::update(
        float deltaTime
    )
    {
        if (paused)
            return;

        deltaTime =
            std::max(
                0.0f,
                deltaTime
            );

        for (Animation* animation :
             animations)
        {
            if (
                animation != nullptr &&
                animation->isActive()
            )
            {
                animation->update(deltaTime);
            }
        }
    }

    void AnimationScheduler::clearFinished()
    {
        animations.erase(
            std::remove_if(
                animations.begin(),
                animations.end(),
                [](Animation* animation)
                {
                    return animation == nullptr ||
                           animation->isFinished();
                }
            ),
            animations.end()
        );
    }

    void AnimationScheduler::clear()
    {
        animations.clear();
    }

    void AnimationScheduler::pause()
    {
        paused = true;
    }

    void AnimationScheduler::resume()
    {
        paused = false;
    }

    bool AnimationScheduler::isPaused() const
    {
        return paused;
    }

    bool AnimationScheduler::isEmpty() const
    {
        return animations.empty();
    }

    size_t AnimationScheduler::count() const
    {
        return animations.size();
    }
}

