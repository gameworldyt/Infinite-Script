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
#include <vector>
#include "Token.h"

class Lexer
{
public:
    std::vector<Token> tokenize(const std::string& source);

private:
    bool isCommand(const std::string& word) const;
    bool isBoolean(const std::string& word) const;
    bool isLogical(const std::string& word) const;
};

