/*
 * InfiniteScript
 *
 * Copyright (c) 2026 InfiniteScript Project.
 * All rights reserved.
 *
 * See LICENSE for licensing terms.
 */

#include "CLI.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <memory>

#include "../Language/Lexer/Lexer.h"
#include "../Language/Parser/Parser.h"
#include "../Language/Runtime/Interpreter.h"
#include "../Engine/UI/UIRuntime.h"

namespace fs = std::filesystem;

namespace
{
    bool containsUI(
        const AST& node)
    {
        if (!node)
            return false;

        if (node->type == NodeType::UI)
            return true;

        for (const auto& child : node->children)
        {
            if (containsUI(child))
                return true;
        }

        return false;
    }
}

void CLI::printHelp() const
{
    std::cout
        << "InfiniteScript Dev CLI\n\n"

        << "Usage:\n"
        << "  Inf <command> [arguments]\n\n"

        << "Commands:\n"
        << "  help                 Show this help message\n"
        << "  version              Show InfiniteScript version\n"
        << "  run <file>           Run an .infs file\n"
        << "  build <file>         Build/check an .infs file\n"
        << "  check <file>         Check an .infs file\n"
        << "  new <name>           Create a new project\n"
        << "  init                 Initialise a project here\n"
        << "  clean                Remove build output\n";
}

void CLI::printVersion() const
{
    std::cout
        << "InfiniteScript v0.2.0\n"
        << "Dev CLI\n";
}

bool CLI::fileExists(
    const std::string& file) const
{
    return fs::exists(file) &&
           fs::is_regular_file(file);
}

bool CLI::directoryExists(
    const std::string& directory) const
{
    return fs::exists(directory) &&
           fs::is_directory(directory);
}

std::string CLI::readFile(
    const std::string& file) const
{
    std::ifstream input(file);

    if (!input)
        throw std::runtime_error(
            "Could not open file: " + file);

    std::ostringstream contents;

    contents << input.rdbuf();

    return contents.str();
}

int CLI::checkFile(
    const std::string& file)
{
    if (!fileExists(file))
    {
        std::cerr
            << "Error [INF1600]\n"
            << "File does not exist: "
            << file
            << '\n';

        return 1;
    }

    try
    {
        std::string source =
            readFile(file);

        Lexer lexer;

        auto tokens =
            lexer.tokenize(source);

        Parser parser(tokens);

        AST program =
            parser.parse();

        if (!program)
        {
            std::cerr
                << "Error [INF1000]\n"
                << "Parser produced no program.\n";

            return 1;
        }

        std::cout
            << "Checked "
            << file
            << " successfully.\n";

        std::cout
            << "Tokens: "
            << tokens.size()
            << '\n';

        if (containsUI(program))
        {
            std::cout
                << "UI program detected.\n";
        }

        return 0;
    }
    catch (const std::exception& error)
    {
        std::cerr
            << "Error [INF1000]\n"
            << error.what()
            << '\n';

        return 1;
    }
}

int CLI::runFile(
    const std::string& file)
{
    if (!fileExists(file))
    {
        std::cerr
            << "Error [INF1600]\n"
            << "File does not exist: "
            << file
            << '\n';

        return 1;
    }

    try
    {
        std::string source =
            readFile(file);

        Lexer lexer;

        auto tokens =
            lexer.tokenize(source);

        Parser parser(tokens);

        AST program =
            parser.parse();

        if (!program)
        {
            std::cerr
                << "Error [INF1000]\n"
                << "Parser produced no program.\n";

            return 1;
        }

        /*
         * Infinite UI programs are handled by the
         * native Windows UI runtime.
         *
         * Normal InfiniteScript programs continue
         * to use the standard interpreter.
         */
        if (containsUI(program))
        {
            UIRuntime uiRuntime;

            if (!uiRuntime.show(program))
            {
                std::cerr
                    << "Error [INF1400]\n"
                    << "Could not start the native Infinite UI runtime.\n";

                return 1;
            }

            return 0;
        }

        Interpreter interpreter;

        interpreter.execute(program);

        return 0;
    }
    catch (const std::exception& error)
    {
        std::cerr
            << "Error [INF2000]\n"
            << error.what()
            << '\n';

        return 1;
    }
}

int CLI::buildFile(
    const std::string& file)
{
    if (!fileExists(file))
    {
        std::cerr
            << "Error [INF1600]\n"
            << "File does not exist: "
            << file
            << '\n';

        return 1;
    }

    try
    {
        std::cout
            << "Building "
            << file
            << "...\n";

        std::string source =
            readFile(file);

        Lexer lexer;

        auto tokens =
            lexer.tokenize(source);

        Parser parser(tokens);

        AST program =
            parser.parse();

        if (!program)
        {
            std::cerr
                << "Error [INF1000]\n"
                << "Parser produced no program.\n";

            return 1;
        }

        std::cout
            << "Build analysis complete.\n";

        std::cout
            << "Tokens: "
            << tokens.size()
            << '\n';

        if (containsUI(program))
        {
            std::cout
                << "Native UI program detected.\n";
        }
        else
        {
            std::cout
                << "Standard InfiniteScript program detected.\n";
        }

        std::cout
            << "Build succeeded.\n";

        return 0;
    }
    catch (const std::exception& error)
    {
        std::cerr
            << "Error [INF2000]\n"
            << error.what()
            << '\n';

        return 1;
    }
}

int CLI::newProject(
    const std::string& name)
{
    if (name.empty())
    {
        std::cerr
            << "Error [INF1002]\n"
            << "Project name cannot be empty.\n";

        return 1;
    }

    fs::path projectPath =
        fs::current_path() / name;

    if (fs::exists(projectPath))
    {
        std::cerr
            << "Error [INF1601]\n"
            << "Project already exists: "
            << name
            << '\n';

        return 1;
    }

    try
    {
        fs::create_directories(
            projectPath / "Packages");

        fs::create_directories(
            projectPath / "Assets");

        fs::create_directories(
            projectPath / "Build");

        std::ofstream projectFile(
            projectPath /
            "InfiniteScript.project");

        projectFile
            << "Name = \""
            << name
            << "\"\n"
            << "Version = \"0.1.0\"\n"
            << "Entry = \"main.infs\"\n";

        projectFile.close();

        std::ofstream mainFile(
            projectPath /
            "main.infs");

        mainFile
            << "Say \"Hello from "
            << name
            << "!\"\n";

        mainFile.close();

        std::cout
            << "Created InfiniteScript project: "
            << name
            << "\n\n"

            << "Project structure:\n"
            << "  "
            << name
            << "/\n"
            << "  +-- main.infs\n"
            << "  +-- InfiniteScript.project\n"
            << "  +-- Packages/\n"
            << "  +-- Assets/\n"
            << "  +-- Build/\n";

        return 0;
    }
    catch (const std::exception& error)
    {
        std::cerr
            << "Error [INF1601]\n"
            << "Could not create project.\n"
            << error.what()
            << '\n';

        return 1;
    }
}

int CLI::initProject()
{
    fs::path current =
        fs::current_path();

    fs::path projectFile =
        current /
        "InfiniteScript.project";

    if (fs::exists(projectFile))
    {
        std::cerr
            << "Error [INF1601]\n"
            << "This directory is already an InfiniteScript project.\n";

        return 1;
    }

    std::string name =
        current.filename().string();

    try
    {
        fs::create_directories(
            current / "Packages");

        fs::create_directories(
            current / "Assets");

        fs::create_directories(
            current / "Build");

        std::ofstream project(
            projectFile);

        project
            << "Name = \""
            << name
            << "\"\n"
            << "Version = \"0.1.0\"\n"
            << "Entry = \"main.infs\"\n";

        project.close();

        if (!fs::exists(
                current / "main.infs"))
        {
            std::ofstream mainFile(
                current / "main.infs");

            mainFile
                << "Say \"Hello from InfiniteScript!\"\n";
        }

        std::cout
            << "Initialised InfiniteScript project in:\n"
            << current.string()
            << '\n';

        return 0;
    }
    catch (const std::exception& error)
    {
        std::cerr
            << "Error [INF1601]\n"
            << "Could not initialise project.\n"
            << error.what()
            << '\n';

        return 1;
    }
}

int CLI::cleanProject()
{
    fs::path build =
        fs::current_path() /
        "Build";

    if (!fs::exists(build))
    {
        std::cout
            << "Nothing to clean.\n";

        return 0;
    }

    try
    {
        fs::remove_all(build);

        fs::create_directories(build);

        std::cout
            << "Build directory cleaned.\n";

        return 0;
    }
    catch (const std::exception& error)
    {
        std::cerr
            << "Error [INF1600]\n"
            << "Could not clean build directory.\n"
            << error.what()
            << '\n';

        return 1;
    }
}

int CLI::run(
    int argc,
    char* argv[])
{
    if (argc < 2)
    {
        printHelp();
        return 0;
    }

    std::string command =
        argv[1];

    if (
        command == "help" ||
        command == "--help" ||
        command == "-h")
    {
        printHelp();
        return 0;
    }

    if (
        command == "version" ||
        command == "--version" ||
        command == "-v")
    {
        printVersion();
        return 0;
    }

    if (command == "run")
    {
        if (argc < 3)
        {
            std::cerr
                << "Error [INF1002]\n"
                << "Missing file argument.\n";

            return 1;
        }

        return runFile(argv[2]);
    }

    if (command == "build")
    {
        if (argc < 3)
        {
            std::cerr
                << "Error [INF1002]\n"
                << "Missing file argument.\n";

            return 1;
        }

        return buildFile(argv[2]);
    }

    if (command == "check")
    {
        if (argc < 3)
        {
            std::cerr
                << "Error [INF1002]\n"
                << "Missing file argument.\n";

            return 1;
        }

        return checkFile(argv[2]);
    }

    if (command == "new")
    {
        if (argc < 3)
        {
            std::cerr
                << "Error [INF1002]\n"
                << "Missing project name.\n";

            return 1;
        }

        return newProject(argv[2]);
    }

    if (command == "init")
    {
        return initProject();
    }

    if (command == "clean")
    {
        return cleanProject();
    }

    std::cerr
        << "Error [INF1101]\n"
        << "\""
        << command
        << "\" is not recognised.\n\n";

    printHelp();

    return 1;
}
