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

using namespace InfiniteScript;

int main()
{
    Animation animation(
        0.0f,
        100.0f,
        1000.0f,
        Easing::EaseOut
    );

    std::cout
        << "Animation state test\n\n";

    while (!animation.isFinished())
    {
        animation.update(16.0f);

        std::cout
            << "Progress: "
            << animation.getProgress() * 100.0f
            << "% | Value: "
            << animation.getValue()
            << "\n";

        std::this_thread::sleep_for(
            std::chrono::milliseconds(16)
        );
    }

    std::cout
        << "\nAnimation finished!\n";

    std::cout
        << "Final value: "
        << animation.getValue()
        << "\n";

    return 0;
}

