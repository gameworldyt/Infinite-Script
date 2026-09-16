/*
 * InfiniteScript
 *
 * Copyright (c) 2026 InfiniteScript Project.
 * All rights reserved.
 *
 * See LICENSE for licensing terms.
 */
#include "Environment.h"

#include <stdexcept>

Environment::Environment(std::shared_ptr<Environment> parent)
    : parent(parent)
{
}

void Environment::defineLocal(
    const std::string& name,
    const RuntimeValue& value)
{
    values[name] = value;
}

void Environment::set(
    const std::string& name,
    const RuntimeValue& value)
{
    if (values.find(name) != values.end())
    {
        values[name] = value;
        return;
    }

    if (parent && parent->exists(name))
    {
        parent->set(name, value);
        return;
    }

    values[name] = value;
}

void Environment::change(
    const std::string& name,
    const RuntimeValue& value)
{
    if (!exists(name))
        throw std::runtime_error("Variable does not exist: " + name);

    RuntimeValue oldValue = get(name);

    if (!std::holds_alternative<double>(oldValue) ||
        !std::holds_alternative<double>(value))
    {
        throw std::runtime_error(
            "Change requires Number variables: " + name);
    }

    set(
        name,
        std::get<double>(oldValue) +
        std::get<double>(value));
}

bool Environment::exists(const std::string& name) const
{
    if (values.find(name) != values.end())
        return true;

    return parent && parent->exists(name);
}

RuntimeValue Environment::get(const std::string& name) const
{
    auto found = values.find(name);

    if (found != values.end())
        return found->second;

    if (parent)
        return parent->get(name);

    throw std::runtime_error(
        "Variable does not exist: " + name);
}

std::shared_ptr<Environment> Environment::getParent() const
{
    return parent;
}

