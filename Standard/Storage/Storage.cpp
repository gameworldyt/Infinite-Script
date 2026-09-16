/*
 * InfiniteScript
 *
 * Copyright (c) 2026 InfiniteScript Project.
 * All rights reserved.
 *
 * See LICENSE for licensing terms.
 */
#include "Storage.h"

std::unordered_map<
    std::string,
    std::string> Storage::values;

void Storage::set(
    const std::string& key,
    const std::string& value)
{
    values[key] = value;
}

std::string Storage::get(
    const std::string& key)
{
    auto found = values.find(key);

    if (found == values.end())
        return "";

    return found->second;
}

bool Storage::exists(
    const std::string& key)
{
    return values.find(key) != values.end();
}

