/*
 * InfiniteScript
 *
 * Copyright (c) 2026 InfiniteScript Project.
 * All rights reserved.
 *
 * See LICENSE for licensing terms.
 */
#include <iostream>
#include <string>

#include "..\Lexer\Lexer.h"
#include "..\Parser\AST.h"
#include "..\Parser\Parser.h"

using namespace InfiniteScript;

void printNode(
    const std::shared_ptr<ASTNode>& node,
    int depth = 0
)
{
    if (node == nullptr)
        return;

    for (int i = 0; i < depth; ++i)
    {
        std::cout << "  ";
    }

    std::cout
        << nodeTypeName(node->type);

    if (!node->value.empty())
    {
        std::cout
            << " ["
            << node->value
            << "]";
    }

    std::cout << "\n";

    for (const auto& child : node->children)
    {
        printNode(
            child,
            depth + 1
        );
    }
}

int main()
{
    std::cout
        << "====================================\n";

    std::cout
        << " InfiniteScript Parser v1 Test\n";

    std::cout
        << "====================================\n\n";

    std::string source =
        "Say \"Hello World\"\n"
        "Set Money = 500\n"
        "Change Money 100\n"
        "If Money > 100\n"
        "    Say \"Rich!\"\n"
        "End\n";

    Lexer lexer(source);

    std::vector<Token> tokens =
        lexer.tokenize();

    std::cout
        << "[Tokens]\n";

    for (const Token& token : tokens)
    {
        std::cout
            << tokenTypeName(token.type);

        if (!token.text.empty())
        {
            std::cout
                << " ["
                << token.text
                << "]";
        }

        std::cout
            << " ("
            << token.line
            << ":"
            << token.column
            << ")\n";
    }

    std::cout << "\n[AST]\n";

    Parser parser(tokens);

    std::shared_ptr<ASTNode> tree =
        parser.parse();

    printNode(tree);

    std::cout
        << "\n====================================\n";

    std::cout
        << " Parser test complete!\n";

    std::cout
        << "====================================\n";

    return 0;
}

