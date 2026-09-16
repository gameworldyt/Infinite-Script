/*
 * InfiniteScript
 *
 * Copyright (c) 2026 InfiniteScript Project.
 * All rights reserved.
 *
 * See LICENSE for licensing terms.
 */
#include "PackageManager.h"

bool PackageManager::registerPackage(
    const PackageMetadata& package)
{
    packages[package.name] = package;
    return true;
}

bool PackageManager::hasPackage(
    const std::string& name) const
{
    return packages.find(name) !=
           packages.end();
}

PackageMetadata PackageManager::getPackage(
    const std::string& name) const
{
    auto found = packages.find(name);

    if (found == packages.end())
        return {};

    return found->second;
}

