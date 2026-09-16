/*
 * InfiniteScript
 *
 * Copyright (c) 2026 InfiniteScript Project.
 * All rights reserved.
 *
 * See LICENSE for licensing terms.
 */
#include "AnimationGroup.h"

namespace InfiniteScript
{
    void AnimationGroup::add(
        Animation* animation
    )
    {
        if (animation != nullptr)
        {
            animations.push_back(
                animation
            );
        }
    }


    void AnimationGroup::update(
        float deltaTime
    )
    {
        for (Animation* animation :
             animations)
        {
            if (
                animation != nullptr &&
                !animation->isFinished()
            )
            {
                animation->update(
                    deltaTime
                );
            }
        }
    }


    void AnimationGroup::reset()
    {
        for (Animation* animation :
             animations)
        {
            if (animation != nullptr)
                animation->reset();
        }
    }


    bool AnimationGroup::isFinished() const
    {
        for (Animation* animation :
             animations)
        {
            if (
                animation != nullptr &&
                !animation->isFinished()
            )
            {
                return false;
            }
        }

        return true;
    }


    size_t AnimationGroup::count() const
    {
        return animations.size();
    }
}


