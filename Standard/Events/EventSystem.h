/*
 * InfiniteScript
 *
 * Copyright (c) 2026 InfiniteScript Project.
 * All rights reserved.
 *
 * See LICENSE for licensing terms.
 */
#pragma once

#include <functional>
#include <string>
#include <unordered_map>

class EventSystem
{
public:
    using Callback = std::function<void()>;

    static void on(
        const std::string& event,
        Callback callback);

    static void emit(
        const std::string& event);

private:
    static std::unordered_map<
        std::string,
        std::vector<Callback>> handlers;
};

