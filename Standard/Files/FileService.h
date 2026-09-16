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

class FileService
{
public:
    static bool exists(
        const std::string& path);

    static std::string read(
        const std::string& path);

    static bool write(
        const std::string& path,
        const std::string& content);
};

