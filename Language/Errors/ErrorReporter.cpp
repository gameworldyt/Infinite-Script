/*
 * InfiniteScript
 *
 * Copyright (c) 2026 InfiniteScript Project.
 * All rights reserved.
 *
 * See LICENSE for licensing terms.
 */
#include "ErrorReporter.h"

#include <sstream>

void ErrorReporter::report(
    ErrorCode code,
    const std::string& message,
    const std::string& file,
    int line,
    int column)
{
    errors.emplace_back(
        code,
        message,
        file,
        line,
        column);
}

void ErrorReporter::report(
    const Error& error)
{
    errors.push_back(error);
}

bool ErrorReporter::hasErrors() const
{
    return !errors.empty();
}

size_t ErrorReporter::count() const
{
    return errors.size();
}

const std::vector<Error>&
ErrorReporter::getErrors() const
{
    return errors;
}

void ErrorReporter::clear()
{
    errors.clear();
}

std::string ErrorReporter::format(
    const Error& error) const
{
    std::ostringstream output;

    output
        << "Error ["
        << errorCodeToString(error.code)
        << "]\n";

    if (!error.file.empty())
    {
        output
            << "File: "
            << error.file
            << '\n';
    }

    if (error.line > 0)
    {
        output
            << "Line: "
            << error.line
            << '\n';
    }

    if (error.column > 0)
    {
        output
            << "Column: "
            << error.column
            << '\n';
    }

    output << '\n';

    output << error.message << '\n';

    if (!error.suggestions.empty())
    {
        output << "\nDid you mean:\n";

        for (const auto& suggestion :
             error.suggestions)
        {
            output
                << "    "
                << suggestion
                << '\n';
        }
    }

    return output.str();
}

std::string ErrorReporter::formatAll() const
{
    std::ostringstream output;

    for (size_t i = 0;
         i < errors.size();
         ++i)
    {
        output << format(errors[i]);

        if (i + 1 < errors.size())
            output << '\n';
    }

    return output.str();
}

