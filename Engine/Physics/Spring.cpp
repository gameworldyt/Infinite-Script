/*
 * InfiniteScript
 *
 * Copyright (c) 2026 InfiniteScript Project.
 * All rights reserved.
 *
 * See LICENSE for licensing terms.
 */
#include <cmath>

#include "Spring.h"

namespace InfiniteScript
{
    Spring::Spring(
        float initial,
        float targetValue,
        float stiffnessValue,
        float dampingValue
    )
        : position(initial),
          velocity(0.0f),
          target(targetValue),
          stiffness(stiffnessValue),
          damping(dampingValue),
          settled(false)
    {
    }


    void Spring::update(
        float deltaTime
    )
    {
        if (deltaTime <= 0.0f)
            return;

        float displacement =
            target - position;

        float acceleration =
            displacement * stiffness -
            velocity * damping;

        velocity +=
            acceleration * (
                deltaTime / 1000.0f
            );

        position +=
            velocity * (
                deltaTime / 1000.0f
            );

        if (
            std::abs(
                target - position
            ) < 0.001f &&
            std::abs(velocity) < 0.001f
        )
        {
            position = target;
            velocity = 0.0f;
            settled = true;
        }
        else
        {
            settled = false;
        }
    }


    void Spring::setTarget(
        float targetValue
    )
    {
        target = targetValue;
        settled = false;
    }


    float Spring::getValue() const
    {
        return position;
    }


    float Spring::getVelocity() const
    {
        return velocity;
    }


    bool Spring::isSettled() const
    {
        return settled;
    }


    void Spring::reset()
    {
        position = target;
        velocity = 0.0f;
        settled = true;
    }
}


