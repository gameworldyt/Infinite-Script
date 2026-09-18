/*
 * InfiniteScript
 *
 * Copyright (c) 2026 InfiniteScript Project.
 * All rights reserved.
 *
 * See LICENSE for licensing terms.
 */

#include "Package.h"

#include <filesystem>
#include <fstream>
#include <stdexcept>
#include <string>

namespace fs = std::filesystem;

namespace
{
    std::string trim(
        const std::string& value)
    {
        const std::string whitespace =
            " \t\r\n";

        const std::size_t first =
            value.find_first_not_of(whitespace);

        if (first == std::string::npos)
            return "";

        const std::size_t last =
            value.find_last_not_of(whitespace);

        return value.substr(
            first,
            last - first + 1);
    }

    std::string removeQuotes(
        const std::string& value)
    {
        std::string result =
            trim(value);

        if (
            result.size() >= 2 &&
            result.front() == '"' &&
            result.back() == '"')
        {
            return result.substr(
                1,
                result.size() - 2);
        }

        return result;
    }
}

Package::Package()
{
}

bool Package::load(
    const std::string& packageDirectory)
{
    fs::path root =
        fs::absolute(packageDirectory);

    if (
        !fs::exists(root) ||
        !fs::is_directory(root))
    {
        throw std::runtime_error(
            "Package directory does not exist: " +
            root.string());
    }

    fs::path manifest =
        root / "package.infs";

    if (!fs::exists(manifest))
    {
        throw std::runtime_error(
            "Package manifest not found: " +
            manifest.string());
    }

    std::ifstream input(manifest);

    if (!input)
    {
        throw std::runtime_error(
            "Could not open package manifest: " +
            manifest.string());
    }

    std::string line;

    while (std::getline(input, line))
    {
        line = trim(line);

        if (
            line.empty() ||
            line[0] == '#' ||
            line[0] == ';')
        {
            continue;
        }

        const std::size_t equals =
            line.find('=');

        if (equals == std::string::npos)
            continue;

        std::string key =
            trim(line.substr(0, equals));

        std::string value =
            removeQuotes(
                line.substr(equals + 1));

        if (key == "Package")
            name = value;
        else if (key == "Version")
            version = value;
        else if (key == "Entry")
            entry = value;
    }

    if (name.empty())
        throw std::runtime_error(
            "Package manifest is missing Package.");

    if (version.empty())
        throw std::runtime_error(
            "Package manifest is missing Version.");

    if (entry.empty())
        throw std::runtime_error(
            "Package manifest is missing Entry.");

    fs::path entryFile =
        root / entry;

    if (
        !fs::exists(entryFile) ||
        !fs::is_regular_file(entryFile))
    {
        throw std::runtime_error(
            "Package entry file does not exist: " +
            entryFile.string());
    }

    directory =
        root.string();

    loaded = true;

    return true;
}

const std::string&
Package::getName() const
{
    return name;
}

const std::string&
Package::getVersion() const
{
    return version;
}

const std::string&
Package::getEntry() const
{
    return entry;
}

const std::string&
Package::getDirectory() const
{
    return directory;
}

bool Package::isLoaded() const
{
    return loaded;
}
