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

    std::string readFile(
        const std::string& file) const;

    bool fileExists(
        const std::string& file) const;

    bool directoryExists(
        const std::string& directory) const;
};
