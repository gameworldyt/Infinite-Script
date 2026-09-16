/*
 * InfiniteScript
 *
 * Copyright (c) 2026 InfiniteScript Project.
 * All rights reserved.
 *
 * See LICENSE for licensing terms.
 */
#include "RandomService.h"

#include <random>

int RandomService::number(
    int min,
    int max)
{
    static std::random_device device;
    static std::mt19937 generator(device());

    std::uniform_int_distribution<int>
        distribution(min, max);

    return distribution(generator);
}

