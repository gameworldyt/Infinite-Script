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

enum class TokenType
{
    Command,
    Identifier,
    Number,
    String,
    Boolean,

    Equal,
    EqualEqual,
    Greater,
    Less,
    GreaterEqual,
    LessEqual,

    Plus,
    Minus,
    Multiply,
    Divide,

    Comma,

    And,
    Or,

    NewLine,
    Indent,
    Dedent,
    EndOfFile,
    Unknown
};

struct Token
{
    TokenType type;
    std::string text;
    int line;
    int column;

    Token(
        TokenType type,
        const std::string& text,
        int line,
        int column)
        : type(type),
          text(text),
          line(line),
          column(column)
    {
    }
};
