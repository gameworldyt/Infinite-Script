/*
 * InfiniteScript
 *
 * Copyright (c) 2026 InfiniteScript Project.
 * All rights reserved.
 *
 * See LICENSE for licensing terms.
 */
#pragma once

#include "FrameTimer.h"
#include "AnimationManager.h"

namespace InfiniteScript
{
    class AnimationLoop
    {
    private:
        FrameTimer timer;

        AnimationManager* manager;

        bool running = false;

    public:

        AnimationLoop(
            AnimationManager* animationManager
        );

        void start();

        void stop();

        bool isRunning() const;
    };
}

