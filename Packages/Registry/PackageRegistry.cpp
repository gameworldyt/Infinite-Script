/*
 * InfiniteScript
 *
 * Copyright (c) 2026 InfiniteScript Project.
 * All rights reserved.
 *
 * See LICENSE for licensing terms.
 */

#include "PackageRegistry.h"

PackageRegistry::PackageRegistry()
{
}

bool PackageRegistry::registerPackage(
    const std::shared_ptr<Package>& package)
{
    if (!package)
        return false;

    if (!package->isLoaded())
        return false;

    const std::string& name =
        package->getName();

    if (name.empty())
        return false;

    if (contains(name))
        return false;

    packages[name] =
        package;

    return true;
}

bool PackageRegistry::unregisterPackage(
    const std::string& name)
{
    return packages.erase(name) > 0;
}

bool PackageRegistry::contains(
    const std::string& name) const
{
    return packages.find(name) !=
           packages.end();
}

std::shared_ptr<Package>
PackageRegistry::get(
    const std::string& name) const
{
    auto found =
        packages.find(name);

    if (found == packages.end())
        return nullptr;

    return found->second;
}

std::vector<std::string>
PackageRegistry::getPackageNames() const
{
    std::vector<std::string> names;

    names.reserve(
        packages.size());

    for (const auto& pair : packages)
        names.push_back(pair.first);

    return names;
}

std::size_t
PackageRegistry::size() const
{
    return packages.size();
}

void PackageRegistry::clear()
{
    packages.clear();
}
