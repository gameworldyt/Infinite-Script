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
#include <vector>

enum class NodeType
{
    Program,
    Block,

    Literal,
    Variable,
    BinaryExpression,

    Say,
    Set,
    Change,

    If,
    ElseIf,
    Else,

    FunctionDeclaration,
    FunctionCall,
    Return,

    While,
    For,
    Break,
    Continue,

    Input,
    Random,
    LocalStorage,

    // Events
    EventHandler,

    // Packages
    PackageDeclaration,
    Import,
    Export,

    // Infinite UI
    UI,
    UIWindow,
    UIText,
    UIButton,
    UISize,
    UITitle,

    // UI events
    UIClick
};

struct ASTNode
{
    NodeType type;
    std::string value;
    std::vector<std::shared_ptr<ASTNode>> children;

    int line = 0;
    int column = 0;

    ASTNode(
        NodeType type,
        const std::string& value = "",
        int line = 0,
        int column = 0)
        : type(type),
          value(value),
          line(line),
          column(column)
    {
    }
};

using AST = std::shared_ptr<ASTNode>;
