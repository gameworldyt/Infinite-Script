/*
 * InfiniteScript
 *
 * Copyright (c) 2026 InfiniteScript Project.
 * All rights reserved.
 *
 * See LICENSE for licensing terms.
 */
#include <algorithm>

#include "Animation.h"

namespace InfiniteScript
{
    Animation::Animation(
        float start,
        float end,
        float durationMilliseconds,
        Easing easingType
    )
        : startValue(start),
          endValue(end),
          duration(
              std::max(
                  0.001f,
                  durationMilliseconds
              )
          ),
          elapsed(0.0f),
          currentValue(start),
          progress(0.0f),
          easing(easingType),
          finished(false),
          paused(false),
          cancelled(false),
          repeatCount(0),
          completedRepeats(0)
    {
    }


    void Animation::update(float deltaTime)
    {
        if (
            finished ||
            paused ||
            cancelled
        )
        {
            return;
        }

        deltaTime =
            std::max(
                0.0f,
                deltaTime
            );

        elapsed += deltaTime;

        while (elapsed >= duration)
        {
            elapsed -= duration;

            completedRepeats++;

            if (
                repeatCount >= 0 &&
                completedRepeats > repeatCount
            )
            {
                elapsed = duration;
                progress = 1.0f;

                currentValue =
                    endValue;

                finished = true;

                if (onUpdate)
                    onUpdate();

                if (onComplete)
                    onComplete();

                return;
            }
        }

        progress =
            elapsed / duration;

        float eased =
            applyEasing(
                progress,
                easing
            );

        currentValue =
            startValue +
            (
                endValue -
                startValue
            ) * eased;

        if (onUpdate)
            onUpdate();
    }


    void Animation::pause()
    {
        paused = true;
    }


    void Animation::resume()
    {
        if (!cancelled && !finished)
            paused = false;
    }


    void Animation::cancel()
    {
        cancelled = true;
        finished = true;
    }


    void Animation::reset()
    {
        elapsed = 0.0f;
        progress = 0.0f;

        currentValue =
            startValue;

        finished = false;
        paused = false;
        cancelled = false;

        completedRepeats = 0;
    }


    void Animation::reverse()
    {
        std::swap(
            startValue,
            endValue
        );

        elapsed =
            duration - elapsed;

        progress =
            elapsed / duration;

        currentValue =
            startValue +
            (
                endValue -
                startValue
            ) *
            applyEasing(
                progress,
                easing
            );

        finished = false;
        cancelled = false;
    }


    void Animation::setRepeatCount(
        int count
    )
    {
        repeatCount =
            std::max(
                0,
                count
            );
    }


    void Animation::setOnComplete(
        std::function<void()> callback
    )
    {
        onComplete =
            callback;
    }


    void Animation::setOnUpdate(
        std::function<void()> callback
    )
    {
        onUpdate =
            callback;
    }


    float Animation::getValue() const
    {
        return currentValue;
    }


    float Animation::getProgress() const
    {
        return progress;
    }


    float Animation::getDuration() const
    {
        return duration;
    }


    bool Animation::isFinished() const
    {
        return finished;
    }


    bool Animation::isPaused() const
    {
        return paused;
    }


    bool Animation::isCancelled() const
    {
        return cancelled;
    }


    bool Animation::isActive() const
    {
        return !finished &&
               !cancelled &&
               !paused;
    }
}


