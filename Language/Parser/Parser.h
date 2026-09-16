#pragma once

#include <vector>
#include <string>
#include <memory>

#include "../Lexer/Token.h"
#include "AST.h"

class Parser
{
public:
    explicit Parser(
        const std::vector<Token>& tokens);

    AST parse();

private:
    const std::vector<Token>& tokens;
    size_t current = 0;

    bool isAtEnd() const;

    const Token& peek() const;
    const Token& previous() const;

    bool check(TokenType type) const;

    bool checkCommand(
        const std::string& command) const;

    const Token& advance();

    bool match(TokenType type);

    bool matchCommand(
        const std::string& command);

    AST parseStatement();

    AST parseExpression();

    AST parseOr();
    AST parseAnd();
    AST parseComparison();
    AST parseTerm();
    AST parseFactor();
    AST parsePrimary();

    AST parseSet();
    AST parseChange();
    AST parseSay();

    AST parseIf();

    AST parseFunction();
    AST parseReturn();

    AST parseWhile();
    AST parseFor();

    AST parseBreak();
    AST parseContinue();

    AST parseInput();
    AST parseRandom();

    AST parseLocalStorage();

    AST parseEvent();

    AST parsePackage();
    AST parseImport();
    AST parseExport();

    // Infinite UI
    AST parseUI();
    AST parseWindow();
    AST parseText();
    AST parseButton();
    AST parseTitle();
    AST parseSize();
    AST parseUIEvent();

    AST parseBlock();

    bool isBlockTerminator() const;
};
