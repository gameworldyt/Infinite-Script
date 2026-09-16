/*
 * InfiniteScript
 *
 * Copyright (c) 2026 InfiniteScript Project.
 * All rights reserved.
 *
 * See LICENSE for licensing terms.
 */
#include "InputService.h"

#include <iostream>

std::string InputService::readLine(
    const std::string& variableName)
{
    std::cout << variableName << ": ";

    std::string value;
    std::getline(std::cin, value);

    return value;
}

