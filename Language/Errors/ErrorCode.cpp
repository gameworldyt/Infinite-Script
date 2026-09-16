/*
 * InfiniteScript
 *
 * Copyright (c) 2026 InfiniteScript Project.
 * All rights reserved.
 *
 * See LICENSE for licensing terms.
 */
#include "ErrorCode.h"

std::string errorCodeToString(ErrorCode code)
{
    return "INF" +
           std::to_string(
               static_cast<int>(code));
}

ErrorCategory errorCategory(ErrorCode code)
{
    int value = static_cast<int>(code);

    if (value >= 1000 && value <= 1099)
        return ErrorCategory::Syntax;

    if (value >= 1100 && value <= 1199)
        return ErrorCategory::Command;

    if (value >= 1200 && value <= 1299)
        return ErrorCategory::Variable;

    if (value >= 1300 && value <= 1399)
        return ErrorCategory::Function;

    if (value >= 1400 && value <= 1499)
        return ErrorCategory::UI;

    if (value >= 1500 && value <= 1599)
        return ErrorCategory::Backend;

    if (value >= 1600 && value <= 1699)
        return ErrorCategory::FileStorage;

    if (value >= 1700 && value <= 1799)
        return ErrorCategory::Event;

    if (value >= 1800 && value <= 1899)
        return ErrorCategory::Security;

    if (value >= 2000 && value <= 2099)
        return ErrorCategory::Runtime;

    return ErrorCategory::Internal;
}

