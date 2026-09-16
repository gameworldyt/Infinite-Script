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

using namespace InfiniteScript;

void testEasing(
    const char* name,
    Easing easing
)
{
    Animation animation(
        0.0f,
        100.0f,
        1000.0f,
        easing
    );

    animation.update(250.0f);

    std::cout
        << name
        << " at 25%: "
        << animation.getValue()
        << "\n";
}


int main()
{
    std::cout
        << "InfiniteScript Easing Test\n\n";


    testEasing(
        "Linear",
        Easing::Linear
    );


    testEasing(
        "EaseIn",
        Easing::EaseIn
    );


    testEasing(
        "EaseOut",
        Easing::EaseOut
    );


    testEasing(
        "EaseInOut",
        Easing::EaseInOut
    );


    testEasing(
        "EaseInCubic",
        Easing::EaseInCubic
    );


    testEasing(
        "EaseOutCubic",
        Easing::EaseOutCubic
    );


    testEasing(
        "EaseInOutCubic",
        Easing::EaseInOutCubic
    );


    testEasing(
        "EaseInQuart",
        Easing::EaseInQuart
    );


    testEasing(
        "EaseOutQuart",
        Easing::EaseOutQuart
    );


    testEasing(
        "EaseInOutQuart",
        Easing::EaseInOutQuart
    );


    testEasing(
        "EaseInQuint",
        Easing::EaseInQuint
    );


    testEasing(
        "EaseOutQuint",
        Easing::EaseOutQuint
    );


    testEasing(
        "EaseInOutQuint",
        Easing::EaseInOutQuint
    );


    return 0;
}

