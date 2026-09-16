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
#include "..\Animation\AnimationState.h"
#include "..\Animation\AnimationTrack.h"
#include "..\Animation\Interpolation.h"
#include "..\Animation\PropertyTrack.h"
#include "..\Animation\RepeatMode.h"
#include "..\Animation\Keyframe.h"
#include "..\Easing\Easing.h"
#include "..\Math\Vector2.h"
#include "..\Math\Vector3.h"
#include "..\Math\Color.h"

using namespace InfiniteScript;

int main()
{
    std::cout << "====================================\n";
    std::cout << " InfiniteScript Final Animation Test\n";
    std::cout << "====================================\n\n";

    std::cout << "[1] Float interpolation\n";

    float floatResult =
        interpolate(
            0.0f,
            100.0f,
            0.5f
        );

    std::cout
        << "Result: "
        << floatResult
        << "\n\n";


    std::cout << "[2] Vector2 interpolation\n";

    Vector2 vector2Result =
        interpolate(
            Vector2(0.0f, 0.0f),
            Vector2(500.0f, 300.0f),
            0.5f
        );

    std::cout
        << "X: "
        << vector2Result.x
        << " | Y: "
        << vector2Result.y
        << "\n\n";


    std::cout << "[3] Vector3 interpolation\n";

    Vector3 vector3Result =
        interpolate(
            Vector3(0.0f, 0.0f, 0.0f),
            Vector3(100.0f, 200.0f, 300.0f),
            0.5f
        );

    std::cout
        << "X: "
        << vector3Result.x
        << " | Y: "
        << vector3Result.y
        << " | Z: "
        << vector3Result.z
        << "\n\n";


    std::cout << "[4] Color interpolation\n";

    Color colorResult =
        interpolate(
            Color(0.0f, 0.0f, 0.0f, 1.0f),
            Color(1.0f, 0.5f, 0.25f, 1.0f),
            0.5f
        );

    std::cout
        << "R: "
        << colorResult.r
        << " | G: "
        << colorResult.g
        << " | B: "
        << colorResult.b
        << " | A: "
        << colorResult.a
        << "\n\n";


    std::cout << "[5] AnimationTrack\n";

    AnimationTrack track;

    track.addKeyframe(
        Keyframe(
            0.0f,
            0.0f,
            Easing::Linear
        )
    );

    track.addKeyframe(
        Keyframe(
            500.0f,
            100.0f,
            Easing::EaseInOut
        )
    );

    track.addKeyframe(
        Keyframe(
            1000.0f,
            200.0f,
            Easing::EaseOut
        )
    );

    track.update(250.0f);

    std::cout
        << "At 250ms: "
        << track.getValue()
        << "\n";

    track.update(750.0f);

    std::cout
        << "At 750ms: "
        << track.getValue()
        << "\n";

    track.update(1000.0f);

    std::cout
        << "At 1000ms: "
        << track.getValue()
        << "\n";

    std::cout
        << "Keyframes: "
        << track.getCount()
        << "\n";

    std::cout
        << "Duration: "
        << track.getDuration()
        << "ms\n\n";


    std::cout << "[6] PropertyTrack\n";

    float propertyFloat = 0.0f;

    PropertyTrack floatTrack(
        &propertyFloat,
        0.0f,
        100.0f
    );

    floatTrack.update(0.5f);

    std::cout
        << "Float property: "
        << propertyFloat
        << "\n";


    Vector2 propertyVector2;

    PropertyTrack vector2Track(
        &propertyVector2,
        Vector2(0.0f, 0.0f),
        Vector2(500.0f, 300.0f)
    );

    vector2Track.update(0.5f);

    std::cout
        << "Vector2 property: "
        << propertyVector2.x
        << ", "
        << propertyVector2.y
        << "\n";


    Vector3 propertyVector3;

    PropertyTrack vector3Track(
        &propertyVector3,
        Vector3(0.0f, 0.0f, 0.0f),
        Vector3(100.0f, 200.0f, 300.0f)
    );

    vector3Track.update(0.5f);

    std::cout
        << "Vector3 property: "
        << propertyVector3.x
        << ", "
        << propertyVector3.y
        << ", "
        << propertyVector3.z
        << "\n\n";


    std::cout << "[7] Animation state\n";

    AnimationState state =
        AnimationState::Running;

    std::cout
        << "State: Running\n\n";


    std::cout << "[8] Repeat mode\n";

    RepeatMode repeatMode =
        RepeatMode::PingPong;

    std::cout
        << "Mode: PingPong\n\n";


    std::cout << "====================================\n";
    std::cout << " Final animation test complete!\n";
    std::cout << "====================================\n";

    return 0;
}
