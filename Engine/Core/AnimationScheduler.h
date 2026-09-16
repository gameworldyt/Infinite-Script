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
    class AnimationScheduler
    {
    private:
        std::vector<Animation*> animations;

        bool paused;

    public:
        AnimationScheduler();

        void add(
            Animation* animation
        );

        void update(
            float deltaTime
        );

        void clearFinished();

        void clear();

        void pause();

        void resume();

        bool isPaused() const;

        bool isEmpty() const;

        size_t count() const;
    };
}

