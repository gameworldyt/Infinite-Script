#include "EventSystem.h"

#include <utility>

std::unordered_map<
    std::string,
    std::vector<EventSystem::Callback>>
    EventSystem::handlers;

void EventSystem::on(
    const std::string& event,
    Callback callback)
{
    handlers[event].push_back(
        std::move(callback));
}

void EventSystem::emit(
    const std::string& event)
{
    auto found =
        handlers.find(event);

    if (found == handlers.end())
        return;

    for (const auto& callback :
         found->second)
    {
        if (callback)
            callback();
    }
}
