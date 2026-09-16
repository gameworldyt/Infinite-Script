/*
 * InfiniteScript
 *
 * Copyright (c) 2026 InfiniteScript Project.
 * All rights reserved.
 *
 * See LICENSE for licensing terms.
 */
#include <iostream>
#include <thread>
#include <chrono>

#include "..\Animation\Animation.h"
#include "..\Easing\Easing.h"
#include "..\Core\AnimationClock.h"
#include "..\Core\AnimationScheduler.h"

using namespace InfiniteScript;

int main()
{
    std::cout
        << "====================================\n"
        << " InfiniteScript Scheduler Test\n"
        << "====================================\n\n";

    AnimationClock clock;

    AnimationScheduler scheduler;

    Animation moveX(
        0.0f,
        500.0f,
        1000.0f,
        Easing::EaseOutCubic
    );

    Animation moveY(
        0.0f,
        300.0f,
        1500.0f,
        Easing::EaseInOut
    );

    scheduler.add(&moveX);
    scheduler.add(&moveY);

    std::cout
        << "Animations registered: "
        << scheduler.count()
        << "\n\n";

    clock.start();

    while (!scheduler.isEmpty())
    {
        float deltaTime =
            clock.tick();

        scheduler.update(deltaTime);

        scheduler.clearFinished();

        std::cout
            << "\rX: "
            << moveX.getValue()
            << " | Y: "
            << moveY.getValue()
            << " | Active: "
            << scheduler.count()
            << std::flush;

        std::this_thread::sleep_for(
            std::chrono::milliseconds(16)
        );
    }

    std::cout
        << "\n\n";

    std::cout
        << "Final X: "
        << moveX.getValue()
        << "\n";

    std::cout
        << "Final Y: "
        << moveY.getValue()
        << "\n";

    std::cout
        << "\n====================================\n"
        << " Scheduler test complete!\n"
        << "====================================\n";

    return 0;
}

