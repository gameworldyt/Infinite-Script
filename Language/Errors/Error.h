/*
 * InfiniteScript
 *
 * Copyright (c) 2026 InfiniteScript Project.
 * All rights reserved.
 *
 * See LICENSE for licensing terms.
 */
#pragma once

#include "ErrorCode.h"

#include <string>
#include <vector>

struct Error
{
    ErrorCode code;
    std::string message;

    std::string file;
    int line = 0;
    int column = 0;

    std::vector<std::string> suggestions;

    Error(
        ErrorCode code,
        const std::string& message,
        const std::string& file = "",
        int line = 0,
        int column = 0)
        : code(code),
          message(message),
          file(file),
          line(line),
          column(column)
    {
    }
};

