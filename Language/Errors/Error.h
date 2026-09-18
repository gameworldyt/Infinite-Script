#pragma once

#include <stdexcept>
#include <string>

class InfiniteScriptError :
    public std::runtime_error
{
public:
    InfiniteScriptError(
        const std::string& code,
        const std::string& message,
        const std::string& file = "",
        int line = 0,
        int column = 0);

    const std::string& code() const noexcept;

    const std::string& file() const noexcept;

    int line() const noexcept;

    int column() const noexcept;

    const std::string& message() const noexcept;

    std::string formatted() const;

private:
    std::string errorCode;
    std::string errorFile;
    std::string errorMessage;

    int errorLine;
    int errorColumn;
};
