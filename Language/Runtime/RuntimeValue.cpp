/*
 * InfiniteScript
 *
 * Copyright (c) 2026 InfiniteScript Project.
 * All rights reserved.
 *
 * See LICENSE for licensing terms.
 */
#include "RuntimeValue.h"

#include <sstream>

RuntimeType getRuntimeType(const RuntimeValue& value)
{
    if (std::holds_alternative<std::monostate>(value))
        return RuntimeType::Null;

    if (std::holds_alternative<double>(value))
        return RuntimeType::Number;

    if (std::holds_alternative<std::string>(value))
        return RuntimeType::String;

    return RuntimeType::Boolean;
}

std::string valueToString(const RuntimeValue& value)
{
    if (std::holds_alternative<std::monostate>(value))
        return "null";

    if (std::holds_alternative<double>(value))
    {
        std::ostringstream output;
        output << std::get<double>(value);
        return output.str();
    }

    if (std::holds_alternative<std::string>(value))
        return std::get<std::string>(value);

    return std::get<bool>(value) ? "true" : "false";
}

bool isTruthy(const RuntimeValue& value)
{
    if (std::holds_alternative<std::monostate>(value))
        return false;

    if (std::holds_alternative<bool>(value))
        return std::get<bool>(value);

    if (std::holds_alternative<double>(value))
        return std::get<double>(value) != 0.0;

    return !std::get<std::string>(value).empty();
}

bool valuesEqual(const RuntimeValue& left, const RuntimeValue& right)
{
    if (getRuntimeType(left) != getRuntimeType(right))
        return false;

    if (std::holds_alternative<std::monostate>(left))
        return true;

    if (std::holds_alternative<double>(left))
        return std::get<double>(left) == std::get<double>(right);

    if (std::holds_alternative<std::string>(left))
        return std::get<std::string>(left) == std::get<std::string>(right);

    return std::get<bool>(left) == std::get<bool>(right);
}

