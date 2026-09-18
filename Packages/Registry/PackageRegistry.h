/*
 * InfiniteScript
 *
 * Copyright (c) 2026 InfiniteScript Project.
 * All rights reserved.
 *
 * See LICENSE for licensing terms.
 */
#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "../Package/Package.h"

class PackageRegistry
{
public:
    PackageRegistry();

    bool registerPackage(
        const std::shared_ptr<Package>& package);

    bool unregisterPackage(
        const std::string& name);

    bool contains(
        const std::string& name) const;

    std::shared_ptr<Package>
    get(
        const std::string& name) const;

    std::vector<std::string>
    getPackageNames() const;

    std::size_t size() const;

    void clear();

private:
    std::unordered_map<
        std::string,
        std::shared_ptr<Package>>
        packages;
};
