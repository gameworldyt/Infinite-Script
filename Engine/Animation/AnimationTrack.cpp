/*
 * InfiniteScript
 *
 * Copyright (c) 2026 InfiniteScript Project.
 * All rights reserved.
 *
 * See LICENSE for licensing terms.
 */
#include <algorithm>

#include "AnimationTrack.h"

#include "..\Easing\Easing.h"

namespace InfiniteScript
{
    AnimationTrack::AnimationTrack()
        : currentValue(0.0f)
    {
    }

    void AnimationTrack::addKeyframe(
        const Keyframe& keyframe
    )
    {
        keyframes.push_back(keyframe);

        std::sort(
            keyframes.begin(),
            keyframes.end(),
            [](const Keyframe& a, const Keyframe& b)
            {
                return a.time < b.time;
            }
        );

        if (keyframes.size() == 1)
        {
            currentValue = keyframes[0].value;
        }
    }

    void AnimationTrack::update(
        float time
    )
    {
        if (keyframes.empty())
        {
            currentValue = 0.0f;
            return;
        }

        if (time <= keyframes.front().time)
        {
            currentValue = keyframes.front().value;
            return;
        }

        if (time >= keyframes.back().time)
        {
            currentValue = keyframes.back().value;
            return;
        }

        for (size_t i = 0; i + 1 < keyframes.size(); ++i)
        {
            const Keyframe& first = keyframes[i];
            const Keyframe& second = keyframes[i + 1];

            if (
                time >= first.time &&
                time <= second.time
            )
            {
                float range =
                    second.time - first.time;

                float localTime =
                    time - first.time;

                float progress =
                    localTime / range;

                float eased =
                    applyEasing(
                        progress,
                        first.easing
                    );

                currentValue =
                    first.value +
                    (second.value - first.value) *
                    eased;

                return;
            }
        }
    }

    float AnimationTrack::getValue() const
    {
        return currentValue;
    }

    float AnimationTrack::getDuration() const
    {
        if (keyframes.empty())
            return 0.0f;

        return keyframes.back().time;
    }

    size_t AnimationTrack::getCount() const
    {
        return keyframes.size();
    }

    void AnimationTrack::clear()
    {
        keyframes.clear();
        currentValue = 0.0f;
    }
}
