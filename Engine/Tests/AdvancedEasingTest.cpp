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
        << "InfiniteScript Advanced Easing Test\n\n";


    testEasing(
        "EaseInExpo",
        Easing::EaseInExpo
    );

    testEasing(
        "EaseOutExpo",
        Easing::EaseOutExpo
    );

    testEasing(
        "EaseInOutExpo",
        Easing::EaseInOutExpo
    );


    testEasing(
        "EaseInCirc",
        Easing::EaseInCirc
    );

    testEasing(
        "EaseOutCirc",
        Easing::EaseOutCirc
    );

    testEasing(
        "EaseInOutCirc",
        Easing::EaseInOutCirc
    );


    testEasing(
        "EaseInBack",
        Easing::EaseInBack
    );

    testEasing(
        "EaseOutBack",
        Easing::EaseOutBack
    );

    testEasing(
        "EaseInOutBack",
        Easing::EaseInOutBack
    );


    testEasing(
        "EaseInElastic",
        Easing::EaseInElastic
    );

    testEasing(
        "EaseOutElastic",
        Easing::EaseOutElastic
    );

    testEasing(
        "EaseInOutElastic",
        Easing::EaseInOutElastic
    );


    testEasing(
        "EaseInBounce",
        Easing::EaseInBounce
    );

    testEasing(
        "EaseOutBounce",
        Easing::EaseOutBounce
    );

    testEasing(
        "EaseInOutBounce",
        Easing::EaseInOutBounce
    );


    return 0;
}

