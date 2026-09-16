/*
 * InfiniteScript
 *
 * Copyright (c) 2026 InfiniteScript Project.
 * All rights reserved.
 *
 * See LICENSE for licensing terms.
 */
#include <algorithm>

#include "Timeline.h"
#include "..\Easing\Easing.h"

namespace InfiniteScript
{
    Timeline::Timeline()
        : duration(0.0f),
          elapsed(0.0f),
          currentValue(0.0f),
          finished(false)
    {
    }


    void Timeline::addKeyframe(
        const Keyframe& keyframe
    )
    {
        keyframes.push_back(
            keyframe
        );

        std::sort(
            keyframes.begin(),
            keyframes.end(),
            [](const Keyframe& a,
               const Keyframe& b)
            {
                return a.time < b.time;
            }
        );

        if (!keyframes.empty())
        {
            duration =
                keyframes.back().time;

            currentValue =
                keyframes.front().value;
        }
    }


    void Timeline::update(
        float deltaTime
    )
    {
        if (
            finished ||
            keyframes.empty()
        )
        {
            return;
        }

        elapsed +=
            std::max(
                0.0f,
                deltaTime
            );

        if (elapsed >= duration)
        {
            elapsed = duration;

            currentValue =
                keyframes.back().value;

            finished = true;

            return;
        }

        if (
            elapsed <=
            keyframes.front().time
        )
        {
            currentValue =
                keyframes.front().value;

            return;
        }

        for (
            size_t i = 1;
            i < keyframes.size();
            i++
        )
        {
            const Keyframe& previous =
                keyframes[i - 1];

            const Keyframe& next =
                keyframes[i];

            if (
                elapsed <=
                next.time
            )
            {
                float segment =
                    next.time -
                    previous.time;

                float local =
                    (
                        elapsed -
                        previous.time
                    ) / segment;

                float eased =
                    applyEasing(
                        local,
                        next.easing
                    );

                currentValue =
                    previous.value +
                    (
                        next.value -
                        previous.value
                    ) * eased;

                return;
            }
        }
    }


    float Timeline::getValue() const
    {
        return currentValue;
    }


    float Timeline::getProgress() const
    {
        if (duration <= 0.0f)
            return 1.0f;

        return elapsed / duration;
    }


    bool Timeline::isFinished() const
    {
        return finished;
    }


    void Timeline::reset()
    {
        elapsed = 0.0f;
        finished = false;

        if (!keyframes.empty())
        {
            currentValue =
                keyframes.front().value;
        }
    }


    void Timeline::clear()
    {
        keyframes.clear();

        duration = 0.0f;
        elapsed = 0.0f;
        currentValue = 0.0f;
        finished = false;
    }
}


