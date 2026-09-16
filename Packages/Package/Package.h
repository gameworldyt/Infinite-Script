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
#include <vector>

struct PackageMetadata
{
    std::string name;
    std::string version;
    std::string author;

    std::vector<std::string>
        dependencies;
};

