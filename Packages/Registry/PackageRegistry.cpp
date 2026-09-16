/*
 * InfiniteScript
 *
 * Copyright (c) 2026 InfiniteScript Project.
 * All rights reserved.
 *
 * See LICENSE for licensing terms.
 */
#include "PackageRegistry.h"

#include <cctype>

bool PackageRegistry::isValidName(
    const std::string& name)
{
    if (name.empty())
        return false;

    for (char c : name)
    {
        if (!std::isalnum(
                static_cast<unsigned char>(c)) &&
            c != '_' &&
            c != '-')
        {
            return false;
        }
    }

    return true;
}

bool PackageRegistry::isValidVersion(
    const std::string& version)
{
    if (version.empty())
        return false;

    bool dotSeen = false;

    for (char c : version)
    {
        if (c == '.')
        {
            if (dotSeen)
                return false;

            dotSeen = true;
            continue;
        }

        if (!std::isdigit(
                static_cast<unsigned char>(c)))
        {
            return false;
        }
    }

    return true;
}

