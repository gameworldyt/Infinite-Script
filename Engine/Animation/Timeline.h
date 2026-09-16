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

#include "..\Animation\Keyframe.h"

namespace InfiniteScript
{
    class Timeline
    {
    private:
        std::vector<Keyframe> keyframes;

        float duration;
        float elapsed;

        float currentValue;

        bool finished;

    public:
        Timeline();

        void addKeyframe(
            const Keyframe& keyframe
        );

        void update(
            float deltaTime
        );

        float getValue() const;

        float getProgress() const;

        bool isFinished() const;

        void reset();

        void clear();
    };
}

