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

class Package
{
public:
    Package();

    bool load(
        const std::string& directory);

    const std::string& getName() const;
    const std::string& getVersion() const;
    const std::string& getEntry() const;
    const std::string& getDirectory() const;

    bool isLoaded() const;

private:
    std::string name;
    std::string version;
    std::string entry;
    std::string directory;

    bool loaded = false;
};
