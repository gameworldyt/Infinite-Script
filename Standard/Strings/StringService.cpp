/*
 * InfiniteScript
 *
 * Copyright (c) 2026 InfiniteScript Project.
 * All rights reserved.
 *
 * See LICENSE for licensing terms.
 */
#include "StringService.h"

int StringService::length(
    const std::string& value)
{
    return static_cast<int>(
        value.size());
}

bool StringService::contains(
    const std::string& value,
    const std::string& search)
{
    return value.find(search) !=
           std::string::npos;
}

