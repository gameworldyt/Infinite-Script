/*
 * InfiniteScript
 *
 * Copyright (c) 2026 InfiniteScript Project.
 * All rights reserved.
 *
 * See LICENSE for licensing terms.
 */
#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "../Parser/AST.h"
#include "../../Packages/PackageManager/PackageManager.h"
#include "Environment.h"

struct FunctionDefinition
{
    std::vector<std::string> parameters;
    std::vector<AST> body;
};

class Interpreter
{
public:
    Interpreter();

    void execute(
        const AST& program);

    void executeNode(
        const AST& node);

    RuntimeValue evaluate(
        const AST& node);

    std::shared_ptr<Environment>
    getEnvironment() const;

    void setPackageDirectory(
        const std::string& directory);

private:
    std::shared_ptr<Environment> environment;

    std::unordered_map<
        std::string,
        FunctionDefinition>
        functions;

    std::unique_ptr<PackageManager>
        packageManager;

    bool returning = false;
    bool breaking = false;
    bool continuing = false;

    RuntimeValue returnValue;

    int loopSafetyLimit = 100000;

    void executeBlock(
        const std::vector<AST>& nodes);

    void executeIf(
        const AST& node);

    void executeWhile(
        const AST& node);

    void executeFor(
        const AST& node);

    void registerFunction(
        const AST& node);

    void registerEvent(
        const AST& node);

    void importPackage(
        const AST& node);

    RuntimeValue callFunction(
        const std::string& name,
        const std::vector<AST>& arguments);

    RuntimeValue evaluateBinary(
        const AST& node);

    RuntimeValue parseLiteral(
        const std::string& value);
};
