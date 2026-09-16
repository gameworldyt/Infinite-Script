/*
 * InfiniteScript
 *
 * Copyright (c) 2026 InfiniteScript Project.
 * All rights reserved.
 *
 * See LICENSE for licensing terms.
 */
#include "AnimationManager.h"

namespace InfiniteScript
{
    void AnimationManager::add(
        Animation* animation
    )
    {
        if (animation != nullptr)
        {
            animations.push_back(animation);
        }
    }


    void AnimationManager::update(
        float deltaTime
    )
    {
        for (Animation* animation : animations)
        {
            if (
                animation != nullptr &&
                !animation->isFinished()
            )
            {
                animation->update(deltaTime);
            }
        }
    }


    void AnimationManager::clearFinished()
    {
        std::vector<Animation*> active;

        for (Animation* animation : animations)
        {
            if (
                animation != nullptr &&
                !animation->isFinished()
            )
            {
                active.push_back(animation);
            }
        }

        animations = active;
    }


    void AnimationManager::clear()
    {
        animations.clear();
    }


    size_t AnimationManager::count() const
    {
        return animations.size();
    }
}

