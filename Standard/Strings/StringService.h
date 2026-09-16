/*
 * InfiniteScript
 *
 * Copyright (c) 2026 InfiniteScript Project.
 * All rights reserved.
 *
 * See LICENSE for licensing terms.
 */
#pragma once

#include <string>

class StringService
{
public:
    static int length(
        const std::string& value);

    static bool contains(
        const std::string& value,
        const std::string& search);
};

