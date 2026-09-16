/*
 * InfiniteScript
 *
 * Copyright (c) 2026 InfiniteScript Project.
 * All rights reserved.
 *
 * See LICENSE for licensing terms.
 */
#include "Lexer.h"

#include <cctype>
#include <sstream>

bool Lexer::isCommand(
    const std::string& word) const
{
    static const std::vector<std::string> commands =
    {
        "Say",
        "Set",
        "Change",

        "Input",
        "Random",

        "If",
        "Else",
        "End",

        "Function",
        "Return",

        "While",
        "For",

        "Break",
        "Continue",

        "On",

        "Package",
        "Import",
        "Export",

        "Local",
        "Storage",

        // Infinite UI
        "UI",
        "Window",
        "Title",
        "Size",
        "Text",
        "Content",
        "Button",
        "Click"
    };

    for (const auto& command : commands)
    {
        if (word == command)
            return true;
    }

    return false;
}

bool Lexer::isBoolean(
    const std::string& word) const
{
    return word == "true" ||
           word == "false";
}

bool Lexer::isLogical(
    const std::string& word) const
{
    return word == "And" ||
           word == "Or";
}

std::vector<Token> Lexer::tokenize(
    const std::string& source)
{
    std::vector<Token> tokens;

    std::istringstream input(source);

    std::string lineText;

    int lineNumber = 1;

    while (std::getline(
        input,
        lineText))
    {
        int position = 0;
        int indentation = 0;

        while (
            position <
                static_cast<int>(
                    lineText.size()) &&
            lineText[position] == ' ')
        {
            indentation++;
            position++;
        }

        while (
            position <
                static_cast<int>(
                    lineText.size()) &&
            lineText[position] == '\t')
        {
            indentation += 4;
            position++;
        }

        if (
            position >=
            static_cast<int>(
                lineText.size()))
        {
            lineNumber++;
            continue;
        }

        // Comment
        if (
            lineText[position] == '/' &&
            position + 1 <
                static_cast<int>(
                    lineText.size()) &&
            lineText[position + 1] == '-')
        {
            lineNumber++;
            continue;
        }

        tokens.push_back(
            Token(
                TokenType::Indent,
                std::to_string(indentation),
                lineNumber,
                1));

        while (
            position <
            static_cast<int>(
                lineText.size()))
        {
            char c =
                lineText[position];

            int column =
                position + 1;

            if (
                std::isspace(
                    static_cast<unsigned char>(
                        c)))
            {
                position++;
                continue;
            }

            // String
            if (c == '"')
            {
                position++;

                std::string value;

                while (
                    position <
                        static_cast<int>(
                            lineText.size()) &&
                    lineText[position] != '"')
                {
                    value +=
                        lineText[position];

                    position++;
                }

                if (
                    position <
                    static_cast<int>(
                        lineText.size()))
                {
                    position++;
                }

                tokens.push_back(
                    Token(
                        TokenType::String,
                        value,
                        lineNumber,
                        column));

                continue;
            }

            // Number
            if (
                std::isdigit(
                    static_cast<unsigned char>(
                        c)) ||
                (
                    c == '-' &&
                    position + 1 <
                        static_cast<int>(
                            lineText.size()) &&
                    std::isdigit(
                        static_cast<unsigned char>(
                            lineText[position + 1]))
                ))
            {
                std::string number;

                if (c == '-')
                {
                    number += c;
                    position++;
                }

                while (
                    position <
                        static_cast<int>(
                            lineText.size()) &&
                    (
                        std::isdigit(
                            static_cast<unsigned char>(
                                lineText[position])) ||
                        lineText[position] == '.'
                    ))
                {
                    number +=
                        lineText[position];

                    position++;
                }

                tokens.push_back(
                    Token(
                        TokenType::Number,
                        number,
                        lineNumber,
                        column));

                continue;
            }

            // Identifier / command
            if (
                std::isalpha(
                    static_cast<unsigned char>(
                        c)) ||
                c == '_')
            {
                std::string word;

                while (
                    position <
                        static_cast<int>(
                            lineText.size()) &&
                    (
                        std::isalnum(
                            static_cast<unsigned char>(
                                lineText[position])) ||
                        lineText[position] == '_'
                    ))
                {
                    word +=
                        lineText[position];

                    position++;
                }

                if (isBoolean(word))
                {
                    tokens.push_back(
                        Token(
                            TokenType::Boolean,
                            word,
                            lineNumber,
                            column));
                }
                else if (isLogical(word))
                {
                    tokens.push_back(
                        Token(
                            word == "And"
                                ? TokenType::And
                                : TokenType::Or,
                            word,
                            lineNumber,
                            column));
                }
                else if (isCommand(word))
                {
                    tokens.push_back(
                        Token(
                            TokenType::Command,
                            word,
                            lineNumber,
                            column));
                }
                else
                {
                    tokens.push_back(
                        Token(
                            TokenType::Identifier,
                            word,
                            lineNumber,
                            column));
                }

                continue;
            }

            // =
            if (c == '=')
            {
                if (
                    position + 1 <
                        static_cast<int>(
                            lineText.size()) &&
                    lineText[position + 1] == '=')
                {
                    tokens.push_back(
                        Token(
                            TokenType::EqualEqual,
                            "==",
                            lineNumber,
                            column));

                    position += 2;
                }
                else
                {
                    tokens.push_back(
                        Token(
                            TokenType::Equal,
                            "=",
                            lineNumber,
                            column));

                    position++;
                }

                continue;
            }

            // >
            if (c == '>')
            {
                if (
                    position + 1 <
                        static_cast<int>(
                            lineText.size()) &&
                    lineText[position + 1] == '=')
                {
                    tokens.push_back(
                        Token(
                            TokenType::GreaterEqual,
                            ">=",
                            lineNumber,
                            column));

                    position += 2;
                }
                else
                {
                    tokens.push_back(
                        Token(
                            TokenType::Greater,
                            ">",
                            lineNumber,
                            column));

                    position++;
                }

                continue;
            }

            // <
            if (c == '<')
            {
                if (
                    position + 1 <
                        static_cast<int>(
                            lineText.size()) &&
                    lineText[position + 1] == '=')
                {
                    tokens.push_back(
                        Token(
                            TokenType::LessEqual,
                            "<=",
                            lineNumber,
                            column));

                    position += 2;
                }
                else
                {
                    tokens.push_back(
                        Token(
                            TokenType::Less,
                            "<",
                            lineNumber,
                            column));

                    position++;
                }

                continue;
            }

            // +
            if (c == '+')
            {
                tokens.push_back(
                    Token(
                        TokenType::Plus,
                        "+",
                        lineNumber,
                        column));

                position++;
                continue;
            }

            // -
            if (c == '-')
            {
                if (
                    position + 1 <
                        static_cast<int>(
                            lineText.size()) &&
                    lineText[position + 1] == '/')
                {
                    break;
                }

                tokens.push_back(
                    Token(
                        TokenType::Minus,
                        "-",
                        lineNumber,
                        column));

                position++;
                continue;
            }

            // *
            if (c == '*')
            {
                tokens.push_back(
                    Token(
                        TokenType::Multiply,
                        "*",
                        lineNumber,
                        column));

                position++;
                continue;
            }

            // /
            if (c == '/')
            {
                tokens.push_back(
                    Token(
                        TokenType::Divide,
                        "/",
                        lineNumber,
                        column));

                position++;
                continue;
            }

            // ,
            if (c == ',')
            {
                tokens.push_back(
                    Token(
                        TokenType::Comma,
                        ",",
                        lineNumber,
                        column));

                position++;
                continue;
            }

            // Unknown character
            tokens.push_back(
                Token(
                    TokenType::Unknown,
                    std::string(1, c),
                    lineNumber,
                    column));

            position++;
        }

        tokens.push_back(
            Token(
                TokenType::NewLine,
                "\\n",
                lineNumber,
                static_cast<int>(
                    lineText.size()) + 1));

        tokens.push_back(
            Token(
                TokenType::Dedent,
                "dedent",
                lineNumber,
                1));

        lineNumber++;
    }

    tokens.push_back(
        Token(
            TokenType::EndOfFile,
            "",
            lineNumber,
            1));

    return tokens;
}
