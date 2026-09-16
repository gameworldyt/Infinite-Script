/*
 * InfiniteScript
 *
 * Copyright (c) 2026 InfiniteScript Project.
 * All rights reserved.
 *
 * See LICENSE for licensing terms.
 */
#include <iostream>

#include "../Errors/ErrorCode.h"
#include "../Errors/Error.h"
#include "../Errors/ErrorReporter.h"

int main()
{
    std::cout
        << "====================================\n"
        << " InfiniteScript Phase 5.1 Test\n"
        << " Error System Foundation\n"
        << "====================================\n\n";

    ErrorReporter reporter;

    reporter.report(
        ErrorCode::INF1101,
        "\"Sya\" is not recognised.",
        "Examples\\Hello.infs",
        2,
        1);

    Error unknownVariable(
        ErrorCode::INF1201,
        "Unknown variable \"Mony\".",
        "Examples\\Money.infs",
        2,
        8);

    unknownVariable.suggestions.push_back("Money");

    reporter.report(unknownVariable);

    std::cout
        << reporter.formatAll();

    std::cout
        << "\nErrors: "
        << reporter.count()
        << '\n';

    std::cout
        << "Has errors: "
        << (reporter.hasErrors()
                ? "true"
                : "false")
        << '\n';

    std::cout
        << "\n====================================\n"
        << " Phase 5.1 Test Complete!\n"
        << "====================================\n";

    return 0;
}

