/*
 * InfiniteScript
 *
 * Copyright (c) 2026 InfiniteScript Project.
 * All rights reserved.
 *
 * See LICENSE for licensing terms.
 */
#pragma once

#include "Error.h"

#include <string>
#include <vector>

class ErrorReporter
{
public:
    void report(
        ErrorCode code,
        const std::string& message,
        const std::string& file = "",
        int line = 0,
        int column = 0);

    void report(
        const Error& error);

    bool hasErrors() const;

    size_t count() const;

    const std::vector<Error>& getErrors() const;

    void clear();

    std::string format(
        const Error& error) const;

    std::string formatAll() const;

private:
    std::vector<Error> errors;
};

