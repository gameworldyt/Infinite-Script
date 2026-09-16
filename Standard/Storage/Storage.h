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

class Storage
{
public:
    static void set(
        const std::string& key,
        const std::string& value);

    static std::string get(
        const std::string& key);

    static bool exists(
        const std::string& key);

private:
    static std::unordered_map<
        std::string,
        std::string> values;
};

