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

class PackageManager
{
public:
    PackageManager();

    void discover(
        const std::string& directory);

    bool hasPackage(
        const std::string& name) const;

    std::shared_ptr<Package>
    getPackage(
        const std::string& name) const;

    std::vector<std::shared_ptr<Package>>
    getPackages() const;

    std::size_t packageCount() const;

private:
    std::unordered_map<
        std::string,
        std::shared_ptr<Package>>
        packages;
};
