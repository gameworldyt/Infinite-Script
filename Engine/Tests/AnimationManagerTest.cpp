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

#include "AnimationManager.cpp"

int main()
{
    using namespace InfiniteScript;

    Animation xAnimation(
        0.0f,
        500.0f,
        1000.0f,
        Easing::EaseOut
    );

    Animation yAnimation(
        0.0f,
        300.0f,
        1500.0f,
        Easing::EaseInOut
    );

    Animation sizeAnimation(
        100.0f,
        600.0f,
        2000.0f,
        Easing::EaseIn
    );

    AnimationManager manager;

    manager.add(&xAnimation);
    manager.add(&yAnimation);
    manager.add(&sizeAnimation);

    const float deltaTime = 1000.0f / 60.0f;

    while (manager.count() > 0)
    {
        manager.update(deltaTime);

        float x = xAnimation.updatePosition(
            Vector2(0.0f, 0.0f),
            Vector2(500.0f, 0.0f),
            0.0f
        ).x;

        float y = yAnimation.updatePosition(
            Vector2(0.0f, 0.0f),
            Vector2(0.0f, 300.0f),
            0.0f
        ).y;

        std::cout
            << "\rX: " << x
            << " | Y: " << y
            << " | Size: "
            << sizeAnimation.update(0.0f)
            << "        "
            << std::flush;

        manager.clearFinished();

        std::this_thread::sleep_for(
            std::chrono::milliseconds(16)
        );
    }

    std::cout << "\nAll animations finished!\n";

    return 0;
}

