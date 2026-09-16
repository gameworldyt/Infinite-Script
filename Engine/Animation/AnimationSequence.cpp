/*
 * InfiniteScript
 *
 * Copyright (c) 2026 InfiniteScript Project.
 * All rights reserved.
 *
 * See LICENSE for licensing terms.
 */
#include "AnimationSequence.h"

namespace InfiniteScript
{
    AnimationSequence::AnimationSequence()
        : currentIndex(0),
          finished(false)
    {
    }

    void AnimationSequence::add(
        Animation* animation
    )
    {
        if (animation != nullptr)
        {
            animations.push_back(animation);
            finished = false;
        }
    }

    void AnimationSequence::update(
        float deltaTime
    )
    {
        if (finished)
            return;

        if (animations.empty())
        {
            finished = true;
            return;
        }

        if (currentIndex >= animations.size())
        {
            finished = true;
            return;
        }

        Animation* current =
            animations[currentIndex];

        if (current == nullptr)
        {
            currentIndex++;

            if (currentIndex >= animations.size())
                finished = true;

            return;
        }

        current->update(deltaTime);

        if (current->isFinished())
        {
            currentIndex++;

            if (currentIndex >= animations.size())
                finished = true;
        }
    }

    void AnimationSequence::reset()
    {
        currentIndex = 0;
        finished = false;

        for (Animation* animation :
             animations)
        {
            if (animation != nullptr)
                animation->reset();
        }
    }

    bool AnimationSequence::isFinished() const
    {
        return finished;
    }

    size_t AnimationSequence::count() const
    {
        return animations.size();
    }
}


