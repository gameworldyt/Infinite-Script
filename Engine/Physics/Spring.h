/*
 * InfiniteScript
 *
 * Copyright (c) 2026 InfiniteScript Project.
 * All rights reserved.
 *
 * See LICENSE for licensing terms.
 */
#pragma once

namespace InfiniteScript
{
    class Spring
    {
    private:
        float position;

        float velocity;

        float target;

        float stiffness;

        float damping;

        bool settled;

    public:
        Spring(
            float initial,
            float targetValue,
            float stiffnessValue = 180.0f,
            float dampingValue = 20.0f
        );

        void update(
            float deltaTime
        );

        void setTarget(
            float targetValue
        );

        float getValue() const;

        float getVelocity() const;

        bool isSettled() const;

        void reset();
    };
}

