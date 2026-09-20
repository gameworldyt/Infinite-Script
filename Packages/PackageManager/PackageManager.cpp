/*
 * InfiniteScript
 *
 * Copyright (c) 2026 InfiniteScript Project.
 * All rights reserved.
 *
 * See LICENSE for licensing terms.
 */

#include "PackageManager.h"

#include <filesystem>
#include <memory>
#include <stdexcept>
#include <vector>

namespace fs = std::filesystem;

PackageManager::PackageManager()
{
}

void PackageManager::discover(
    const std::string& directory)
{
    fs::path root =
        fs::absolute(directory);

    if (!fs::exists(root))
    {
        throw std::runtime_error(
            "Package directory does not exist: " +
            root.string());
    }

    if (!fs::is_directory(root))
    {
        throw std::runtime_error(
            "Package path is not a directory: " +
            root.string());
    }

    packages.clear();

    for (
        const auto& entry :
        fs::directory_iterator(root))
    {
        if (!entry.is_directory())
            continue;

        fs::path packageDirectory =
            entry.path();

        fs::path manifest =
            packageDirectory /
            "package.infs";

        if (!fs::exists(manifest))
            continue;

        auto package =
            std::make_shared<Package>();

        package->load(
            packageDirectory.string());

        if (hasPackage(
                package->getName()))
        {
            throw std::runtime_error(
                "Duplicate package name: " +
                package->getName());
        }

        packages[
            package->getName()] =
            package;
    }
}

bool PackageManager::hasPackage(
    const std::string& name) const
{
    return packages.find(name) !=
           packages.end();
}

std::shared_ptr<Package>
PackageManager::getPackage(
    const std::string& name) const
{
    auto found =
        packages.find(name);

    if (found == packages.end())
        return nullptr;

    return found->second;
}

std::vector<std::shared_ptr<Package>>
PackageManager::getPackages() const
{
    std::vector<
        std::shared_ptr<Package>>
        result;

    result.reserve(
        packages.size());

    for (
        const auto& pair :
        packages)
    {
        result.push_back(
            pair.second);
    }

    return result;
}

std::size_t
PackageManager::packageCount() const
{
    return packages.size();
}
