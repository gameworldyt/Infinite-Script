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

class PackageRegistry
{
public:
    static bool isValidName(
        const std::string& name);

    static bool isValidVersion(
        const std::string& version);
};

