/*
 * InfiniteScript
 *
 * Copyright (c) 2026 InfiniteScript Project.
 * All rights reserved.
 *
 * See LICENSE for licensing terms.
 */
#include <cmath>
#include <algorithm>

#include "Easing.h"

namespace InfiniteScript
{
    float applyEasing(
        float t,
        Easing easing
    )
    {
        t = std::clamp(t, 0.0f, 1.0f);

        const float pi =
            3.14159265358979323846f;

        switch (easing)
        {
            case Easing::Linear:
                return t;

            case Easing::EaseIn:
                return t * t;

            case Easing::EaseOut:
                return 1.0f -
                       (1.0f - t) *
                       (1.0f - t);

            case Easing::EaseInOut:
                if (t < 0.5f)
                    return 2.0f * t * t;

                return 1.0f -
                       std::pow(
                           -2.0f * t + 2.0f,
                           2.0f
                       ) / 2.0f;

            case Easing::EaseInCubic:
                return t * t * t;

            case Easing::EaseOutCubic:
                return 1.0f -
                       std::pow(1.0f - t, 3.0f);

            case Easing::EaseInOutCubic:
                if (t < 0.5f)
                    return 4.0f * t * t * t;

                return 1.0f -
                       std::pow(
                           -2.0f * t + 2.0f,
                           3.0f
                       ) / 2.0f;

            case Easing::EaseInQuart:
                return t * t * t * t;

            case Easing::EaseOutQuart:
                return 1.0f -
                       std::pow(1.0f - t, 4.0f);

            case Easing::EaseInOutQuart:
                if (t < 0.5f)
                    return 8.0f * t * t * t * t;

                return 1.0f -
                       std::pow(
                           -2.0f * t + 2.0f,
                           4.0f
                       ) / 2.0f;

            case Easing::EaseInQuint:
                return t * t * t * t * t;

            case Easing::EaseOutQuint:
                return 1.0f -
                       std::pow(1.0f - t, 5.0f);

            case Easing::EaseInOutQuint:
                if (t < 0.5f)
                    return 16.0f *
                           t * t * t * t * t;

                return 1.0f -
                       std::pow(
                           -2.0f * t + 2.0f,
                           5.0f
                       ) / 2.0f;

            case Easing::EaseInExpo:
                if (t == 0.0f)
                    return 0.0f;

                return std::pow(
                    2.0f,
                    10.0f * t - 10.0f
                );

            case Easing::EaseOutExpo:
                if (t == 1.0f)
                    return 1.0f;

                return 1.0f -
                       std::pow(
                           2.0f,
                           -10.0f * t
                       );

            case Easing::EaseInOutExpo:
                if (t == 0.0f)
                    return 0.0f;

                if (t == 1.0f)
                    return 1.0f;

                if (t < 0.5f)
                    return std::pow(
                        2.0f,
                        20.0f * t - 10.0f
                    ) / 2.0f;

                return (
                    2.0f -
                    std::pow(
                        2.0f,
                        -20.0f * t + 10.0f
                    )
                ) / 2.0f;

            case Easing::EaseInCirc:
                return 1.0f -
                       std::sqrt(
                           1.0f - t * t
                       );

            case Easing::EaseOutCirc:
                return std::sqrt(
                    1.0f -
                    (t - 1.0f) *
                    (t - 1.0f)
                );

            case Easing::EaseInOutCirc:
                if (t < 0.5f)
                {
                    return (
                        1.0f -
                        std::sqrt(
                            1.0f -
                            std::pow(
                                2.0f * t,
                                2.0f
                            )
                        )
                    ) / 2.0f;
                }

                return (
                    std::sqrt(
                        1.0f -
                        std::pow(
                            -2.0f * t + 2.0f,
                            2.0f
                        )
                    ) + 1.0f
                ) / 2.0f;

            case Easing::EaseInBack:
            {
                const float c1 = 1.70158f;
                const float c3 = c1 + 1.0f;

                return c3 * t * t * t -
                       c1 * t * t;
            }

            case Easing::EaseOutBack:
            {
                const float c1 = 1.70158f;
                const float c3 = c1 + 1.0f;
                const float x = t - 1.0f;

                return 1.0f +
                       c3 * x * x * x +
                       c1 * x * x;
            }

            case Easing::EaseInOutBack:
            {
                const float c1 = 1.70158f;
                const float c2 = c1 * 1.525f;

                if (t < 0.5f)
                {
                    const float x = 2.0f * t;

                    return (
                        x * x *
                        (
                            (c2 + 1.0f) * x -
                            c2
                        )
                    ) / 2.0f;
                }

                const float x = 2.0f * t - 2.0f;

                return (
                    x * x *
                    (
                        (c2 + 1.0f) * x +
                        c2
                    ) + 2.0f
                ) / 2.0f;
            }

            case Easing::EaseInElastic:
            {
                if (t == 0.0f || t == 1.0f)
                    return t;

                const float c4 =
                    (2.0f * pi) / 3.0f;

                return -std::pow(
                           2.0f,
                           10.0f * t - 10.0f
                       ) *
                       std::sin(
                           (t * 10.0f - 10.75f) *
                           c4
                       );
            }

            case Easing::EaseOutElastic:
            {
                if (t == 0.0f || t == 1.0f)
                    return t;

                const float c4 =
                    (2.0f * pi) / 3.0f;

                return std::pow(
                           2.0f,
                           -10.0f * t
                       ) *
                       std::sin(
                           (t * 10.0f - 0.75f) *
                           c4
                       ) + 1.0f;
            }

            case Easing::EaseInOutElastic:
            {
                if (t == 0.0f || t == 1.0f)
                    return t;

                const float c5 =
                    (2.0f * pi) / 4.5f;

                if (t < 0.5f)
                {
                    return -(
                        std::pow(
                            2.0f,
                            20.0f * t - 10.0f
                        ) *
                        std::sin(
                            (20.0f * t - 11.125f) *
                            c5
                        )
                    ) / 2.0f;
                }

                return (
                    std::pow(
                        2.0f,
                        -20.0f * t + 10.0f
                    ) *
                    std::sin(
                        (20.0f * t - 11.125f) *
                        c5
                    )
                ) / 2.0f + 1.0f;
            }

            case Easing::EaseOutBounce:
            {
                const float n1 = 7.5625f;
                const float d1 = 2.75f;

                if (t < 1.0f / d1)
                    return n1 * t * t;

                if (t < 2.0f / d1)
                {
                    const float x =
                        t - 1.5f / d1;

                    return n1 * x * x + 0.75f;
                }

                if (t < 2.5f / d1)
                {
                    const float x =
                        t - 2.25f / d1;

                    return n1 * x * x + 0.9375f;
                }

                const float x =
                    t - 2.625f / d1;

                return n1 * x * x + 0.984375f;
            }

            case Easing::EaseInBounce:
                return 1.0f -
                       applyEasing(
                           1.0f - t,
                           Easing::EaseOutBounce
                       );

            case Easing::EaseInOutBounce:
                if (t < 0.5f)
                {
                    return (
                        1.0f -
                        applyEasing(
                            1.0f - 2.0f * t,
                            Easing::EaseOutBounce
                        )
                    ) / 2.0f;
                }

                return (
                    1.0f +
                    applyEasing(
                        2.0f * t - 1.0f,
                        Easing::EaseOutBounce
                    )
                ) / 2.0f;
        }

        return t;
    }
}


