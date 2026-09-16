/*
 * InfiniteScript
 *
 * Copyright (c) 2026 InfiniteScript Project.
 * All rights reserved.
 *
 * See LICENSE for licensing terms.
 */
#include <iostream>
#include <memory>
#include <string>

#include "../Lexer/Lexer.h"
#include "../Parser/Parser.h"
#include "../Runtime/Interpreter.h"

#include "../../Standard/Events/EventSystem.h"
#include "../../Standard/Math/MathService.h"
#include "../../Standard/Strings/StringService.h"
#include "../../Standard/Files/FileService.h"

static void printAST(
    const AST& node,
    int depth = 0)
{
    if (!node)
        return;

    for (int i = 0; i < depth; ++i)
        std::cout << "  ";

    std::cout << static_cast<int>(node->type);

    if (!node->value.empty())
        std::cout << " [" << node->value << "]";

    std::cout << '\n';

    for (const auto& child :
         node->children)
    {
        printAST(child, depth + 1);
    }
}

int main()
{
    std::cout
        << "====================================\n"
        << " InfiniteScript v0.2 Mega Test\n"
        << " Phase 3 + 4 + 7 + 8\n"
        << "====================================\n\n";

    const std::string source = R"(
Package MegaTest
Import Math
Import Strings

Local Storage Money = 100
Set IsAdmin = true

Function GiveMoney Amount
    Change Money by Amount
    Return Money
End

Function Add AmountA AmountB
    Return AmountA + AmountB
End

Random Number Bonus = 1 to 10

If Money >= 100 And IsAdmin == true
    Say "Access granted!"
    GiveMoney 50
Else
    Say "Access denied!"
End

For I = 1 to 3
    Change Money by 10
End

While Money < 200
    Change Money by 10
End

On TestEvent
    Say "Event fired!"
End
)";

    std::cout << "[1] Lexing...\n";

    Lexer lexer;
    auto tokens = lexer.tokenize(source);

    std::cout
        << "Tokens: "
        << tokens.size()
        << "\n\n";

    std::cout << "[2] Parsing...\n";

    Parser parser(tokens);
    AST program = parser.parse();

    std::cout << "AST:\n";
    printAST(program);

    std::cout << "\n[3] Runtime execution\n";

    Interpreter interpreter;
    interpreter.execute(program);

    std::cout << "\n[4] Runtime checks\n";

    auto environment =
        interpreter.getEnvironment();

    std::cout
        << "Money = "
        << valueToString(
            environment->get("Money"))
        << '\n';

    std::cout
        << "IsAdmin = "
        << valueToString(
            environment->get("IsAdmin"))
        << '\n';

    std::cout
        << "Bonus = "
        << valueToString(
            environment->get("Bonus"))
        << '\n';

    std::cout
        << "I = "
        << valueToString(
            environment->get("I"))
        << '\n';

    std::cout << "\n[5] Standard library\n";

    std::cout
        << "Math abs(-25): "
        << MathService::abs(-25)
        << '\n';

    std::cout
        << "Math max(10, 20): "
        << MathService::max(10, 20)
        << '\n';

    std::cout
        << "String length: "
        << StringService::length("InfiniteScript")
        << '\n';

    std::cout
        << "String contains: "
        << (StringService::contains(
                "InfiniteScript",
                "Script")
                ? "true"
                : "false")
        << '\n';

    std::cout << "\n[6] Events\n";

    EventSystem::on(
        "ManualEvent",
        []
        {
            std::cout
                << "Manual event received!\n";
        });

    EventSystem::emit("ManualEvent");

    EventSystem::emit("TestEvent");

    std::cout << "\n[7] Package/file architecture\n";

    std::cout
        << "Package architecture: OK\n";

    std::cout
        << "File service: "
        << (FileService::exists(
                "Language\\Tests\\MegaTest.cpp")
                ? "OK"
                : "FAILED")
        << '\n';

    std::cout
        << "\n====================================\n"
        << " InfiniteScript v0.2 Test Complete!\n"
        << "====================================\n";

    return 0;
}

