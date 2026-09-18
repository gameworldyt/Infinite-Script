#pragma once

#include "Error.h"

namespace InfiniteScript
{
    inline std::string formatError(
        const InfiniteScriptError& error)
    {
        return error.formatted();
    }
}
