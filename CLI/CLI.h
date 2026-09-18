/*
 * InfiniteScript
 *
 * Copyright (c) 2026 InfiniteScript Project.
 * All rights reserved.
 *
 * See LICENSE for licensing terms.
 */
#pragma once

#include <filesystem>
#include <string>

class CLI
{
public:
    int run(
        int argc,
        char* argv[]);

private:
    void printHelp() const;
    void printVersion() const;

    int runFile(
        const std::string& file);

    int buildFile(
        const std::string& file);

    int checkFile(
        const std::string& file);

    int newProject(
        const std::string& name);

    int initProject();

    int cleanProject();

    bool isProjectDirectory() const;

    std::filesystem::path
    findProjectFile() const;

    std::string
    getProjectEntry(
        const std::filesystem::path& projectFile) const;

    std::string
    resolveProjectEntry() const;

    std::string readFile(
        const std::string& file) const;

    bool fileExists(
        const std::string& file) const;

    bool directoryExists(
        const std::string& directory) const;
};
