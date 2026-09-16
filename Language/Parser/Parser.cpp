/*
 * InfiniteScript
 *
 * Copyright (c) 2026 InfiniteScript Project.
 * All rights reserved.
 *
 * See LICENSE for licensing terms.
 */

#include "Parser.h"

#include <stdexcept>

Parser::Parser(
    const std::vector<Token>& tokens)
    : tokens(tokens)
{
}

bool Parser::isAtEnd() const
{
    return current >= tokens.size() ||
           tokens[current].type ==
               TokenType::EndOfFile;
}

const Token& Parser::peek() const
{
    return tokens[current];
}

const Token& Parser::previous() const
{
    return tokens[current - 1];
}

bool Parser::check(
    TokenType type) const
{
    if (current >= tokens.size())
        return type ==
            TokenType::EndOfFile;

    return tokens[current].type ==
           type;
}

bool Parser::checkCommand(
    const std::string& command) const
{
    return !isAtEnd() &&
           tokens[current].type ==
               TokenType::Command &&
           tokens[current].text ==
               command;
}

const Token& Parser::advance()
{
    if (!isAtEnd())
        current++;

    return previous();
}

bool Parser::match(
    TokenType type)
{
    if (!check(type))
        return false;

    advance();

    return true;
}

bool Parser::matchCommand(
    const std::string& command)
{
    if (!checkCommand(command))
        return false;

    advance();

    return true;
}

AST Parser::parse()
{
    auto program =
        std::make_shared<ASTNode>(
            NodeType::Program);

    while (!isAtEnd())
    {
        if (
            check(TokenType::NewLine) ||
            check(TokenType::Dedent) ||
            check(TokenType::Indent))
        {
            advance();
            continue;
        }

        AST statement =
            parseStatement();

        if (statement)
        {
            program->children.push_back(
                statement);
        }
        else if (!isAtEnd())
        {
            advance();
        }
    }

    return program;
}

AST Parser::parseStatement()
{
    if (checkCommand("UI"))
        return parseUI();

    if (checkCommand("Window"))
        return parseWindow();

    if (checkCommand("Text"))
        return parseText();

    if (checkCommand("Button"))
        return parseButton();

    if (checkCommand("Title"))
        return parseTitle();

    if (checkCommand("Size"))
        return parseSize();

    if (checkCommand("Say"))
        return parseSay();

    if (checkCommand("Set"))
        return parseSet();

    if (checkCommand("Change"))
        return parseChange();

    if (checkCommand("If"))
        return parseIf();

    if (checkCommand("Function"))
        return parseFunction();

    if (checkCommand("Return"))
        return parseReturn();

    if (checkCommand("While"))
        return parseWhile();

    if (checkCommand("For"))
        return parseFor();

    if (checkCommand("Break"))
        return parseBreak();

    if (checkCommand("Continue"))
        return parseContinue();

    if (checkCommand("Input"))
        return parseInput();

    if (checkCommand("Random"))
        return parseRandom();

    if (checkCommand("Local"))
        return parseLocalStorage();

    if (checkCommand("On"))
        return parseEvent();

    if (checkCommand("Package"))
        return parsePackage();

    if (checkCommand("Import"))
        return parseImport();

    if (checkCommand("Export"))
        return parseExport();

    if (check(TokenType::Identifier))
    {
        Token name =
            advance();

        auto node =
            std::make_shared<ASTNode>(
                NodeType::FunctionCall,
                name.text,
                name.line,
                name.column);

        while (
            !check(TokenType::NewLine) &&
            !check(TokenType::Dedent) &&
            !check(TokenType::EndOfFile))
        {
            AST argument =
                parseExpression();

            if (argument)
                node->children.push_back(
                    argument);
            else
                break;
        }

        return node;
    }

    return nullptr;
}

AST Parser::parseExpression()
{
    return parseOr();
}

AST Parser::parseOr()
{
    AST left =
        parseAnd();

    while (check(TokenType::Or))
    {
        Token op =
            advance();

        AST right =
            parseAnd();

        auto node =
            std::make_shared<ASTNode>(
                NodeType::BinaryExpression,
                op.text,
                op.line,
                op.column);

        node->children.push_back(left);
        node->children.push_back(right);

        left = node;
    }

    return left;
}

AST Parser::parseAnd()
{
    AST left =
        parseComparison();

    while (check(TokenType::And))
    {
        Token op =
            advance();

        AST right =
            parseComparison();

        auto node =
            std::make_shared<ASTNode>(
                NodeType::BinaryExpression,
                op.text,
                op.line,
                op.column);

        node->children.push_back(left);
        node->children.push_back(right);

        left = node;
    }

    return left;
}

AST Parser::parseComparison()
{
    AST left =
        parseTerm();

    while (
        check(TokenType::EqualEqual) ||
        check(TokenType::Greater) ||
        check(TokenType::Less) ||
        check(TokenType::GreaterEqual) ||
        check(TokenType::LessEqual))
    {
        Token op =
            advance();

        AST right =
            parseTerm();

        auto node =
            std::make_shared<ASTNode>(
                NodeType::BinaryExpression,
                op.text,
                op.line,
                op.column);

        node->children.push_back(left);
        node->children.push_back(right);

        left = node;
    }

    return left;
}

AST Parser::parseTerm()
{
    AST left =
        parseFactor();

    while (
        check(TokenType::Plus) ||
        check(TokenType::Minus))
    {
        Token op =
            advance();

        AST right =
            parseFactor();

        auto node =
            std::make_shared<ASTNode>(
                NodeType::BinaryExpression,
                op.text,
                op.line,
                op.column);

        node->children.push_back(left);
        node->children.push_back(right);

        left = node;
    }

    return left;
}

AST Parser::parseFactor()
{
    AST left =
        parsePrimary();

    while (
        check(TokenType::Multiply) ||
        check(TokenType::Divide))
    {
        Token op =
            advance();

        AST right =
            parsePrimary();

        auto node =
            std::make_shared<ASTNode>(
                NodeType::BinaryExpression,
                op.text,
                op.line,
                op.column);

        node->children.push_back(left);
        node->children.push_back(right);

        left = node;
    }

    return left;
}

AST Parser::parsePrimary()
{
    if (check(TokenType::Number))
    {
        Token token =
            advance();

        return std::make_shared<ASTNode>(
            NodeType::Literal,
            token.text,
            token.line,
            token.column);
    }

    if (check(TokenType::String))
    {
        Token token =
            advance();

        return std::make_shared<ASTNode>(
            NodeType::Literal,
            "\"" + token.text + "\"",
            token.line,
            token.column);
    }

    if (check(TokenType::Boolean))
    {
        Token token =
            advance();

        return std::make_shared<ASTNode>(
            NodeType::Literal,
            token.text,
            token.line,
            token.column);
    }

    if (check(TokenType::Identifier))
    {
        Token token =
            advance();

        bool hasArgument =
            !check(TokenType::NewLine) &&
            !check(TokenType::Dedent) &&
            !check(TokenType::EndOfFile) &&
            (
                check(TokenType::Number) ||
                check(TokenType::String) ||
                check(TokenType::Boolean) ||
                check(TokenType::Identifier)
            );

        if (hasArgument)
        {
            auto function =
                std::make_shared<ASTNode>(
                    NodeType::FunctionCall,
                    token.text,
                    token.line,
                    token.column);

            while (
                !check(TokenType::NewLine) &&
                !check(TokenType::Dedent) &&
                !check(TokenType::EndOfFile))
            {
                AST argument =
                    parseExpression();

                if (argument)
                    function->children.push_back(
                        argument);
                else
                    break;
            }

            return function;
        }

        return std::make_shared<ASTNode>(
            NodeType::Variable,
            token.text,
            token.line,
            token.column);
    }

    return nullptr;
}

AST Parser::parseSet()
{
    Token command =
        advance();

    if (!check(TokenType::Identifier))
        throw std::runtime_error(
            "Expected variable name after Set.");

    Token variable =
        advance();

    if (!match(TokenType::Equal))
        throw std::runtime_error(
            "Expected '=' after Set variable.");

    AST expression =
        parseExpression();

    auto node =
        std::make_shared<ASTNode>(
            NodeType::Set,
            variable.text,
            command.line,
            command.column);

    if (expression)
        node->children.push_back(expression);

    return node;
}

AST Parser::parseChange()
{
    Token command =
        advance();

    if (!check(TokenType::Identifier))
        throw std::runtime_error(
            "Expected variable name after Change.");

    Token variable =
        advance();

    if (!matchCommand("by"))
    {
        if (
            check(TokenType::Identifier) &&
            peek().text == "by")
        {
            advance();
        }
        else
        {
            throw std::runtime_error(
                "Expected 'by' after Change variable.");
        }
    }

    AST expression =
        parseExpression();

    auto node =
        std::make_shared<ASTNode>(
            NodeType::Change,
            variable.text,
            command.line,
            command.column);

    if (expression)
        node->children.push_back(expression);

    return node;
}

AST Parser::parseSay()
{
    Token command =
        advance();

    AST expression =
        parseExpression();

    auto node =
        std::make_shared<ASTNode>(
            NodeType::Say,
            "",
            command.line,
            command.column);

    if (expression)
        node->children.push_back(expression);

    return node;
}

AST Parser::parseIf()
{
    Token command =
        advance();

    AST condition =
        parseExpression();

    auto node =
        std::make_shared<ASTNode>(
            NodeType::If,
            "",
            command.line,
            command.column);

    if (condition)
        node->children.push_back(condition);

    AST body =
        parseBlock();

    if (body)
        node->children.push_back(body);

    while (checkCommand("Else"))
    {
        advance();

        if (checkCommand("If"))
        {
            Token elseIfToken =
                advance();

            AST elseIfCondition =
                parseExpression();

            auto elseIf =
                std::make_shared<ASTNode>(
                    NodeType::ElseIf,
                    "",
                    elseIfToken.line,
                    elseIfToken.column);

            if (elseIfCondition)
                elseIf->children.push_back(
                    elseIfCondition);

            AST elseIfBody =
                parseBlock();

            if (elseIfBody)
                elseIf->children.push_back(
                    elseIfBody);

            node->children.push_back(
                elseIf);
        }
        else
        {
            auto elseNode =
                std::make_shared<ASTNode>(
                    NodeType::Else);

            AST elseBody =
                parseBlock();

            if (elseBody)
                elseNode->children.push_back(
                    elseBody);

            node->children.push_back(
                elseNode);

            break;
        }
    }

    return node;
}

AST Parser::parseFunction()
{
    Token command =
        advance();

    if (!check(TokenType::Identifier))
        throw std::runtime_error(
            "Expected function name.");

    Token name =
        advance();

    auto node =
        std::make_shared<ASTNode>(
            NodeType::FunctionDeclaration,
            name.text,
            command.line,
            command.column);

    while (
        !check(TokenType::NewLine) &&
        !check(TokenType::EndOfFile))
    {
        if (check(TokenType::Identifier))
        {
            Token parameter =
                advance();

            node->children.push_back(
                std::make_shared<ASTNode>(
                    NodeType::Variable,
                    parameter.text,
                    parameter.line,
                    parameter.column));
        }
        else
        {
            break;
        }
    }

    AST body =
        parseBlock();

    if (body)
        node->children.push_back(body);

    return node;
}

AST Parser::parseReturn()
{
    Token command =
        advance();

    auto node =
        std::make_shared<ASTNode>(
            NodeType::Return,
            "",
            command.line,
            command.column);

    if (
        !check(TokenType::NewLine) &&
        !check(TokenType::Dedent) &&
        !check(TokenType::EndOfFile))
    {
        AST expression =
            parseExpression();

        if (expression)
            node->children.push_back(expression);
    }

    return node;
}

AST Parser::parseWhile()
{
    Token command =
        advance();

    AST condition =
        parseExpression();

    auto node =
        std::make_shared<ASTNode>(
            NodeType::While,
            "",
            command.line,
            command.column);

    if (condition)
        node->children.push_back(condition);

    AST body =
        parseBlock();

    if (body)
        node->children.push_back(body);

    return node;
}

AST Parser::parseFor()
{
    Token command =
        advance();

    if (!check(TokenType::Identifier))
        throw std::runtime_error(
            "Expected loop variable after For.");

    Token variable =
        advance();

    if (!match(TokenType::Equal))
        throw std::runtime_error(
            "Expected '=' after For variable.");

    AST minimum =
        parseExpression();

    if (
        check(TokenType::Identifier) &&
        peek().text == "to")
    {
        advance();
    }
    else if (checkCommand("to"))
    {
        advance();
    }
    else
    {
        throw std::runtime_error(
            "Expected 'to' in For range.");
    }

    AST maximum =
        parseExpression();

    auto node =
        std::make_shared<ASTNode>(
            NodeType::For,
            variable.text,
            command.line,
            command.column);

    if (minimum)
        node->children.push_back(minimum);

    if (maximum)
        node->children.push_back(maximum);

    AST body =
        parseBlock();

    if (body)
        node->children.push_back(body);

    return node;
}

AST Parser::parseBreak()
{
    Token command =
        advance();

    return std::make_shared<ASTNode>(
        NodeType::Break,
        "",
        command.line,
        command.column);
}

AST Parser::parseContinue()
{
    Token command =
        advance();

    return std::make_shared<ASTNode>(
        NodeType::Continue,
        "",
        command.line,
        command.column);
}

AST Parser::parseInput()
{
    Token command =
        advance();

    std::string type;

    if (
        check(TokenType::Identifier) &&
        (
            peek().text == "Number" ||
            peek().text == "Boolean"
        ))
    {
        type =
            advance().text;
    }

    if (!check(TokenType::Identifier))
        throw std::runtime_error(
            "Expected variable name after Input.");

    Token variable =
        advance();

    auto node =
        std::make_shared<ASTNode>(
            NodeType::Input,
            variable.text,
            command.line,
            command.column);

    if (!type.empty())
    {
        node->value =
            type + ":" +
            variable.text;
    }

    return node;
}

AST Parser::parseRandom()
{
    Token command =
        advance();

    auto node =
        std::make_shared<ASTNode>(
            NodeType::Random,
            "",
            command.line,
            command.column);

    if (
        check(TokenType::Identifier) &&
        peek().text == "Number")
    {
        advance();
    }

    if (!check(TokenType::Identifier))
        throw std::runtime_error(
            "Expected variable name after Random.");

    node->value =
        advance().text;

    if (!match(TokenType::Equal))
        throw std::runtime_error(
            "Expected '=' after Random variable.");

    AST minimum =
        parseExpression();

    if (minimum)
        node->children.push_back(minimum);

    if (
        check(TokenType::Identifier) &&
        peek().text == "to")
    {
        advance();
    }
    else if (checkCommand("to"))
    {
        advance();
    }
    else
    {
        throw std::runtime_error(
            "Expected 'to' in Random range.");
    }

    AST maximum =
        parseExpression();

    if (maximum)
        node->children.push_back(maximum);

    return node;
}

AST Parser::parseLocalStorage()
{
    Token local =
        advance();

    if (!matchCommand("Storage"))
    {
        if (
            check(TokenType::Identifier) &&
            peek().text == "Storage")
        {
            advance();
        }
        else
        {
            throw std::runtime_error(
                "Expected Storage after Local.");
        }
    }

    if (!check(TokenType::Identifier))
        throw std::runtime_error(
            "Expected variable name after Local Storage.");

    Token variable =
        advance();

    if (!match(TokenType::Equal))
        throw std::runtime_error(
            "Expected '=' after Local Storage variable.");

    AST expression =
        parseExpression();

    auto node =
        std::make_shared<ASTNode>(
            NodeType::LocalStorage,
            variable.text,
            local.line,
            local.column);

    if (expression)
        node->children.push_back(expression);

    return node;
}

AST Parser::parseEvent()
{
    Token command =
        advance();

    if (!check(TokenType::Identifier))
        throw std::runtime_error(
            "Expected event name after On.");

    Token eventName =
        advance();

    auto node =
        std::make_shared<ASTNode>(
            NodeType::EventHandler,
            eventName.text,
            command.line,
            command.column);

    AST body =
        parseBlock();

    if (body)
        node->children.push_back(body);

    return node;
}

AST Parser::parsePackage()
{
    Token command =
        advance();

    if (!check(TokenType::Identifier))
        throw std::runtime_error(
            "Expected package name.");

    Token name =
        advance();

    return std::make_shared<ASTNode>(
        NodeType::PackageDeclaration,
        name.text,
        command.line,
        command.column);
}

AST Parser::parseImport()
{
    Token command =
        advance();

    if (!check(TokenType::Identifier))
        throw std::runtime_error(
            "Expected module name after Import.");

    Token name =
        advance();

    return std::make_shared<ASTNode>(
        NodeType::Import,
        name.text,
        command.line,
        command.column);
}

AST Parser::parseExport()
{
    Token command =
        advance();

    if (!check(TokenType::Identifier))
        throw std::runtime_error(
            "Expected export name.");

    Token name =
        advance();

    return std::make_shared<ASTNode>(
        NodeType::Export,
        name.text,
        command.line,
        command.column);
}

/*
 * Infinite UI
 */

AST Parser::parseUI()
{
    Token command =
        advance();

    auto node =
        std::make_shared<ASTNode>(
            NodeType::UI,
            "",
            command.line,
            command.column);

    AST body =
        parseBlock();

    if (body)
        node->children.push_back(body);

    if (checkCommand("End"))
        advance();

    return node;
}

AST Parser::parseWindow()
{
    Token command =
        advance();

    if (!check(TokenType::Identifier))
        throw std::runtime_error(
            "Expected window name after Window.");

    Token name =
        advance();

    auto node =
        std::make_shared<ASTNode>(
            NodeType::UIWindow,
            name.text,
            command.line,
            command.column);

    AST body =
        parseBlock();

    if (body)
        node->children.push_back(body);

    if (checkCommand("End"))
        advance();

    return node;
}

AST Parser::parseText()
{
    Token command =
        advance();

    if (!check(TokenType::Identifier))
        throw std::runtime_error(
            "Expected text element name after Text.");

    Token name =
        advance();

    auto node =
        std::make_shared<ASTNode>(
            NodeType::UIText,
            name.text,
            command.line,
            command.column);

    while (!isAtEnd())
    {
        if (
            check(TokenType::NewLine) ||
            check(TokenType::Indent) ||
            check(TokenType::Dedent))
        {
            advance();
            continue;
        }

        if (checkCommand("Content"))
        {
            Token contentCommand =
                advance();

            AST content =
                parseExpression();

            if (content)
                node->children.push_back(
                    content);

            continue;
        }

        if (checkCommand("End"))
        {
            advance();
            break;
        }

        break;
    }

    return node;
}

AST Parser::parseButton()
{
    Token command =
        advance();

    if (!check(TokenType::Identifier))
        throw std::runtime_error(
            "Expected button name after Button.");

    Token name =
        advance();

    auto node =
        std::make_shared<ASTNode>(
            NodeType::UIButton,
            name.text,
            command.line,
            command.column);

    while (!isAtEnd())
    {
        if (
            check(TokenType::NewLine) ||
            check(TokenType::Indent) ||
            check(TokenType::Dedent))
        {
            advance();
            continue;
        }

        if (checkCommand("Text"))
        {
            Token textCommand =
                advance();

            AST text =
                parseExpression();

            auto textNode =
                std::make_shared<ASTNode>(
                    NodeType::UIText,
                    "",
                    textCommand.line,
                    textCommand.column);

            if (text)
                textNode->children.push_back(
                    text);

            node->children.push_back(
                textNode);

            continue;
        }

        if (checkCommand("On"))
        {
            AST event =
                parseUIEvent();

            if (event)
                node->children.push_back(
                    event);

            continue;
        }

        if (checkCommand("End"))
        {
            advance();
            break;
        }

        break;
    }

    return node;
}

AST Parser::parseUIEvent()
{
    Token command =
        advance();

    if (!checkCommand("Click"))
    {
        if (
            check(TokenType::Identifier) &&
            peek().text == "Click")
        {
            advance();
        }
        else
        {
            throw std::runtime_error(
                "Expected Click after On.");
        }
    }
    else
    {
        advance();
    }

    auto node =
        std::make_shared<ASTNode>(
            NodeType::UIClick,
            "Click",
            command.line,
            command.column);

    AST body =
        parseBlock();

    if (body)
        node->children.push_back(body);

    if (checkCommand("End"))
        advance();

    return node;
}

AST Parser::parseTitle()
{
    Token command =
        advance();

    AST expression =
        parseExpression();

    auto node =
        std::make_shared<ASTNode>(
            NodeType::UITitle,
            "",
            command.line,
            command.column);

    if (expression)
        node->children.push_back(
            expression);

    return node;
}

AST Parser::parseSize()
{
    Token command =
        advance();

    AST width =
        parseExpression();

    if (!match(TokenType::Comma))
        throw std::runtime_error(
            "Expected ',' between UI width and height.");

    AST height =
        parseExpression();

    auto node =
        std::make_shared<ASTNode>(
            NodeType::UISize,
            "",
            command.line,
            command.column);

    if (width)
        node->children.push_back(width);

    if (height)
        node->children.push_back(height);

    return node;
}

AST Parser::parseBlock()
{
    auto block =
        std::make_shared<ASTNode>(
            NodeType::Block);

    while (!isAtEnd())
    {
        if (
            check(TokenType::NewLine) ||
            check(TokenType::Indent) ||
            check(TokenType::Dedent))
        {
            advance();
            continue;
        }

        if (isBlockTerminator())
            break;

        AST statement =
            parseStatement();

        if (statement)
            block->children.push_back(
                statement);
        else
            break;
    }

    return block;
}

bool Parser::isBlockTerminator() const
{
    if (checkCommand("End"))
        return true;

    if (checkCommand("Else"))
        return true;

    return false;
}
