/*
 * InfiniteScript
 *
 * Copyright (c) 2026 InfiniteScript Project.
 * All rights reserved.
 *
 * See LICENSE for licensing terms.
 */
#pragma once

#include <cstddef>
#include <vector>

#include "Keyframe.h"

namespace InfiniteScript
{
    class AnimationTrack
    {
    private:
        std::vector<Keyframe> keyframes;

        float currentValue;

    public:
        AnimationTrack();

        void addKeyframe(
            const Keyframe& keyframe
        );

        void update(
            float time
        );

        float getValue() const;

        float getDuration() const;

        size_t getCount() const;

        void clear();
    };
}
