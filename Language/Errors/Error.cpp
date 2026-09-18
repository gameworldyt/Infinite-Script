#include "Error.h"

#include <sstream>

InfiniteScriptError::InfiniteScriptError(
    const std::string& code,
    const std::string& message,
    const std::string& file,
    int line,
    int column)
    : std::runtime_error(message),
      errorCode(code),
      errorFile(file),
      errorMessage(message),
      errorLine(line),
      errorColumn(column)
{
}

const std::string&
InfiniteScriptError::code() const noexcept
{
    return errorCode;
}

const std::string&
InfiniteScriptError::file() const noexcept
{
    return errorFile;
}

int InfiniteScriptError::line() const noexcept
{
    return errorLine;
}

int InfiniteScriptError::column() const noexcept
{
    return errorColumn;
}

const std::string&
InfiniteScriptError::message() const noexcept
{
    return errorMessage;
}

std::string
InfiniteScriptError::formatted() const
{
    std::ostringstream output;

    output
        << "Error ["
        << errorCode
        << "]\n";

    if (!errorFile.empty())
    {
        output
            << "File: "
            << errorFile
            << '\n';
    }

    if (errorLine > 0)
    {
        output
            << "Line: "
            << errorLine
            << '\n';
    }

    if (errorColumn > 0)
    {
        output
            << "Column: "
            << errorColumn
            << '\n';
    }

    output
        << '\n'
        << errorMessage;

    return output.str();
}
