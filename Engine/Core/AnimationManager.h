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
    class AnimationManager
    {
    private:
        std::vector<Animation*> animations;

    public:

        void add(Animation* animation);

        void update(float deltaTime);

        void clearFinished();

        void clear();

        size_t count() const;
    };
}

