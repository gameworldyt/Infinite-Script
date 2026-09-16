/*
 * InfiniteScript
 *
 * Copyright (c) 2026 InfiniteScript Project.
 * All rights reserved.
 *
 * See LICENSE for licensing terms.
 */
#include "EventSystem.h"

#include <vector>

std::unordered_map<
    std::string,
    std::vector<EventSystem::Callback>>
    EventSystem::handlers;

void EventSystem::on(
    const std::string& event,
    Callback callback)
{
    handlers[event].push_back(callback);
}

void EventSystem::emit(
    const std::string& event)
{
    auto found = handlers.find(event);

    if (found == handlers.end())
        return;

    for (const auto& callback :
         found->second)
    {
        callback();
    }
}

