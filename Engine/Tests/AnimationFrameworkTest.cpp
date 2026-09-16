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
#include "..\Animation\AnimationGroup.h"
#include "..\Animation\AnimationSequence.h"
#include "..\Animation\Timeline.h"
#include "..\Physics\Spring.h"

using namespace InfiniteScript;


int main()
{
    std::cout
        << "====================================\n"
        << " InfiniteScript Animation Framework\n"
        << "====================================\n\n";


    // --------------------------------
    // Basic animation
    // --------------------------------

    float value = 0.0f;

    Animation animation(
        0.0f,
        100.0f,
        500.0f,
        Easing::EaseOutCubic
    );

    animation.setOnComplete(
        []()
        {
            std::cout
                << "Animation completed!\n";
        }
    );

    while (!animation.isFinished())
    {
        animation.update(16.0f);

        value =
            animation.getValue();
    }

    std::cout
        << "Basic animation: "
        << value
        << "\n\n";


    // --------------------------------
    // Timeline
    // --------------------------------

    Timeline timeline;

    timeline.addKeyframe(
        Keyframe(
            0.0f,
            0.0f,
            Easing::Linear
        )
    );

    timeline.addKeyframe(
        Keyframe(
            250.0f,
            100.0f,
            Easing::EaseOutCubic
        )
    );

    timeline.addKeyframe(
        Keyframe(
            500.0f,
            50.0f,
            Easing::EaseInOut
        )
    );

    while (!timeline.isFinished())
    {
        timeline.update(16.0f);
    }

    std::cout
        << "Timeline final value: "
        << timeline.getValue()
        << "\n\n";


    // --------------------------------
    // Animation group
    // --------------------------------

    Animation x(
        0.0f,
        500.0f,
        500.0f,
        Easing::EaseOut
    );

    Animation y(
        0.0f,
        300.0f,
        750.0f,
        Easing::EaseOutCubic
    );

    AnimationGroup group;

    group.add(&x);
    group.add(&y);

    while (!group.isFinished())
    {
        group.update(16.0f);
    }

    std::cout
        << "Group X: "
        << x.getValue()
        << "\n";

    std::cout
        << "Group Y: "
        << y.getValue()
        << "\n\n";


    // --------------------------------
    // Animation sequence
    // --------------------------------

    Animation first(
        0.0f,
        100.0f,
        300.0f
    );

    Animation second(
        100.0f,
        200.0f,
        300.0f
    );

    AnimationSequence sequence;

    sequence.add(&first);
    sequence.add(&second);

    while (!sequence.isFinished())
    {
        sequence.update(16.0f);
    }

    std::cout
        << "Sequence final value: "
        << second.getValue()
        << "\n\n";


    // --------------------------------
    // Spring
    // --------------------------------

    Spring spring(
        0.0f,
        100.0f
    );

    for (int i = 0; i < 300; i++)
    {
        spring.update(16.0f);
    }

    std::cout
        << "Spring value: "
        << spring.getValue()
        << "\n";

    std::cout
        << "Spring settled: "
        << (
            spring.isSettled()
                ? "yes"
                : "no"
        )
        << "\n\n";


    std::cout
        << "====================================\n"
        << " Framework test complete!\n"
        << "====================================\n";

    return 0;
}

