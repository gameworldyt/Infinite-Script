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

#include "FrameTimer.cpp"

int main()
{
    using namespace InfiniteScript;

    FrameTimer timer;

    std::cout << "InfiniteScript Frame Timer Test\n";
    std::cout << "Measuring real frame times...\n\n";

    for (int frame = 1; frame <= 120; frame++)
    {
        float deltaTime = timer.deltaTime();

        std::cout
            << "Frame "
            << frame
            << " | Delta: "
            << deltaTime
            << " ms"
            << std::endl;

        std::this_thread::sleep_for(
            std::chrono::milliseconds(16)
        );
    }

    std::cout << "\nFrame timer test finished!\n";

    return 0;
}

