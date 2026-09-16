/*
 * InfiniteScript
 *
 * Copyright (c) 2026 InfiniteScript Project.
 * All rights reserved.
 *
 * See LICENSE for licensing terms.
 */
#include "MathService.h"

#include <cmath>

double MathService::abs(double value)
{
    return std::abs(value);
}

double MathService::min(double a, double b)
{
    return a < b ? a : b;
}

double MathService::max(double a, double b)
{
    return a > b ? a : b;
}

