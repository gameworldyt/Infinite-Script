/*
 * InfiniteScript
 *
 * Copyright (c) 2026 InfiniteScript Project.
 * All rights reserved.
 *
 * See LICENSE for licensing terms.
 */
#include <iostream>

#include "..\Animation\Animation.h"
#include "AnimationManager.h"
#include "AnimationLoop.h"

using namespace InfiniteScript;

int main()
{
    AnimationManager manager;

    Animation moveX(
        100.0f,
        500.0f,
        1000.0f,
        Easing::EaseOut
    );

    Animation moveY(
        100.0f,
        300.0f,
        1000.0f,
        Easing::EaseInOut
    );

    manager.add(&moveX);
    manager.add(&moveY);

    AnimationLoop loop(&manager);

    std::cout
        << "Starting animation loop...\n";

    loop.start();

    std::cout
        << "\nAnimation loop finished!\n";

    std::cout
        << "Final X: "
        << moveX.getValue()
        << "\n";

    std::cout
        << "Final Y: "
        << moveY.getValue()
        << "\n";

    return 0;
}

