/*
 * InfiniteScript
 *
 * Copyright (c) 2026 InfiniteScript Project.
 * All rights reserved.
 *
 * See LICENSE for licensing terms.
 */
#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "RuntimeValue.h"

class Environment
{
public:
    explicit Environment(std::shared_ptr<Environment> parent = nullptr);

    void set(const std::string& name, const RuntimeValue& value);
    void defineLocal(const std::string& name, const RuntimeValue& value);

    void change(const std::string& name, const RuntimeValue& value);

    bool exists(const std::string& name) const;
    RuntimeValue get(const std::string& name) const;

    std::shared_ptr<Environment> getParent() const;

private:
    std::unordered_map<std::string, RuntimeValue> values;
    std::shared_ptr<Environment> parent;
};

