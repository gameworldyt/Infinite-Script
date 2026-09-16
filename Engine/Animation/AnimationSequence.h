/*
 * InfiniteScript
 *
 * Copyright (c) 2026 InfiniteScript Project.
 * All rights reserved.
 *
 * See LICENSE for licensing terms.
 */
#pragma once

#include <vector>
#include "..\Animation\Animation.h"

namespace InfiniteScript
{
    class AnimationSequence
    {
    private:
        std::vector<Animation*> animations;

        size_t currentIndex;

        bool finished;

    public:
        AnimationSequence();

        void add(
            Animation* animation
        );

        void update(
            float deltaTime
        );

        void reset();

        bool isFinished() const;

        size_t count() const;
    };
}

