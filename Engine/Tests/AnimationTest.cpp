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

#include "Animation.cpp"

int main()
{
    using namespace InfiniteScript;

    Animation animation(
        0.0f,
        1.0f,
        1000.0f,
        Easing::EaseInOut
    );

    Vector2 start(100.0f, 100.0f);
    Vector2 end(500.0f, 300.0f);

    const float deltaTime = 1000.0f / 60.0f;

    while (!animation.isFinished())
    {
        animation.update(deltaTime);

        Vector2 position =
            animation.updatePosition(
                start,
                end,
                deltaTime
            );

        std::cout
            << "\rX: " << position.x
            << "  Y: " << position.y
            << "          "
            << std::flush;

        std::this_thread::sleep_for(
            std::chrono::milliseconds(16)
        );
    }

    std::cout << "\nMovement finished!\n";

    return 0;
}

