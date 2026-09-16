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
#include <unordered_map>

#include "../Package/Package.h"

class PackageManager
{
public:
    bool registerPackage(
        const PackageMetadata& package);

    bool hasPackage(
        const std::string& name) const;

    PackageMetadata getPackage(
        const std::string& name) const;

private:
    std::unordered_map<
        std::string,
        PackageMetadata> packages;
};

