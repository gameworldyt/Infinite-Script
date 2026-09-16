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

enum class ErrorCategory
{
    Syntax,
    Command,
    Variable,
    Function,
    UI,
    Backend,
    FileStorage,
    Event,
    Security,
    Runtime,
    Internal
};

enum class ErrorCode
{
    INF1000 = 1000,
    INF1001 = 1001,
    INF1002 = 1002,

    INF1100 = 1100,
    INF1101 = 1101,
    INF1102 = 1102,

    INF1200 = 1200,
    INF1201 = 1201,
    INF1202 = 1202,

    INF1300 = 1300,
    INF1301 = 1301,
    INF1302 = 1302,

    INF1400 = 1400,
    INF1401 = 1401,

    INF1500 = 1500,
    INF1501 = 1501,

    INF1600 = 1600,
    INF1601 = 1601,

    INF1700 = 1700,
    INF1701 = 1701,

    INF1800 = 1800,
    INF1801 = 1801,

    INF2000 = 2000,
    INF2001 = 2001,
    INF2002 = 2002,

    INF9000 = 9000,
    INF9001 = 9001
};

std::string errorCodeToString(ErrorCode code);
ErrorCategory errorCategory(ErrorCode code);

