/*
 * InfiniteScript
 *
 * Copyright (c) 2026 InfiniteScript Project.
 * All rights reserved.
 *
 * See LICENSE for licensing terms.
 */
#include <thread>
#include <chrono>

#include "AnimationLoop.h"

namespace InfiniteScript
{
    AnimationLoop::AnimationLoop(
        AnimationManager* animationManager
    )
        : manager(animationManager)
    {
    }


    void AnimationLoop::start()
    {
        if (manager == nullptr)
            return;

        running = true;

        timer.reset();

        while (running)
        {
            float deltaTime =
                timer.deltaTime();

            manager->update(deltaTime);

            manager->clearFinished();

            if (manager->count() == 0)
            {
                running = false;
            }

            std::this_thread::sleep_for(
                std::chrono::milliseconds(1)
            );
        }
    }


    void AnimationLoop::stop()
    {
        running = false;
    }


    bool AnimationLoop::isRunning() const
    {
        return running;
    }
}

