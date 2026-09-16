/*
 * InfiniteScript
 *
 * Copyright (c) 2026 InfiniteScript Project.
 * All rights reserved.
 *
 * See LICENSE for licensing terms.
 */
#include "FileService.h"

#include <fstream>
#include <sstream>

bool FileService::exists(
    const std::string& path)
{
    std::ifstream file(path);
    return file.good();
}

std::string FileService::read(
    const std::string& path)
{
    std::ifstream file(path);

    if (!file)
        return "";

    std::stringstream buffer;
    buffer << file.rdbuf();

    return buffer.str();
}

bool FileService::write(
    const std::string& path,
    const std::string& content)
{
    std::ofstream file(path);

    if (!file)
        return false;

    file << content;
    return true;
}

