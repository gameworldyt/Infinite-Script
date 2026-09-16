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
#include <variant>

enum class RuntimeType
{
    Null,
    Number,
    String,
    Boolean
};

using RuntimeValue = std::variant<
    std::monostate,
    double,
    std::string,
    bool
>;

RuntimeType getRuntimeType(const RuntimeValue& value);
std::string valueToString(const RuntimeValue& value);
bool isTruthy(const RuntimeValue& value);
bool valuesEqual(const RuntimeValue& left, const RuntimeValue& right);

