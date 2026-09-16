/*
 * InfiniteScript
 *
 * Copyright (c) 2026 InfiniteScript Project.
 * All rights reserved.
 *
 * See LICENSE for licensing terms.
 */
#include "Interpreter.h"

#include <iostream>
#include <stdexcept>

#include "../../Standard/Input/InputService.h"
#include "../../Standard/Random/RandomService.h"
#include "../../Standard/Storage/Storage.h"
#include "../../Standard/Events/EventSystem.h"

Interpreter::Interpreter()
{
    environment = std::make_shared<Environment>();
}

void Interpreter::execute(const AST& program)
{
    if (!program)
        return;

    for (const auto& node : program->children)
    {
        executeNode(node);

        if (returning)
            break;
    }
}

void Interpreter::executeNode(const AST& node)
{
    if (!node)
        return;

    switch (node->type)
    {
        case NodeType::Program:
        case NodeType::Block:
            executeBlock(node->children);
            break;

        case NodeType::Say:
        {
            if (!node->children.empty())
                std::cout << valueToString(evaluate(node->children[0])) << std::endl;
            else
                std::cout << node->value << std::endl;

            break;
        }

        case NodeType::Set:
        {
            if (node->children.empty())
                throw std::runtime_error("Set requires a value.");

            environment->set(
                node->value,
                evaluate(node->children[0]));

            break;
        }

        case NodeType::Change:
        {
            if (node->children.empty())
                throw std::runtime_error("Change requires a value.");

            RuntimeValue currentValue =
                environment->get(node->value);

            RuntimeValue changeValue =
                evaluate(node->children[0]);

            if (!std::holds_alternative<double>(currentValue) ||
                !std::holds_alternative<double>(changeValue))
            {
                throw std::runtime_error(
                    "Change can only be used with numbers.");
            }

            double result =
                std::get<double>(currentValue) +
                std::get<double>(changeValue);

            environment->set(node->value, result);

            break;
        }

        case NodeType::If:
            executeIf(node);
            break;

        case NodeType::FunctionDeclaration:
            registerFunction(node);
            break;

        case NodeType::FunctionCall:
            callFunction(node->value, node->children);
            break;

        case NodeType::Return:
        {
            if (!node->children.empty())
                returnValue = evaluate(node->children[0]);
            else
                returnValue = std::monostate{};

            returning = true;
            break;
        }

        case NodeType::While:
            executeWhile(node);
            break;

        case NodeType::For:
            executeFor(node);
            break;

        case NodeType::Break:
            breaking = true;
            break;

        case NodeType::Continue:
            continuing = true;
            break;

        case NodeType::Input:
        {
            std::string type = "String";
            std::string variableName = node->value;

            const std::size_t separator =
                variableName.find(':');

            if (separator != std::string::npos)
            {
                type = variableName.substr(0, separator);
                variableName =
                    variableName.substr(separator + 1);
            }

            if (type == "Number")
            {
                double value = 0;

                std::cout << variableName << ": ";
                if (!(std::cin >> value))
                {
                    std::cin.clear();
                    std::string ignored;
                    std::getline(std::cin, ignored);

                    throw std::runtime_error(
                        "Input expected a number.");
                }

                environment->set(variableName, value);
            }
            else if (type == "Boolean")
            {
                std::string input;

                std::cout << variableName << ": ";
                std::cin >> input;

                if (input == "true" ||
                    input == "True" ||
                    input == "TRUE")
                {
                    environment->set(variableName, true);
                }
                else if (input == "false" ||
                         input == "False" ||
                         input == "FALSE")
                {
                    environment->set(variableName, false);
                }
                else
                {
                    throw std::runtime_error(
                        "Input expected true or false.");
                }
            }
            else
            {
                std::string input;

                std::cout << variableName << ": ";
                std::getline(std::cin >> std::ws, input);

                environment->set(variableName, input);
            }

            break;
        }

        case NodeType::Random:
        {
            if (node->children.size() < 2)
                throw std::runtime_error(
                    "Random requires a minimum and maximum.");

            double minimum =
                std::get<double>(evaluate(node->children[0]));

            double maximum =
                std::get<double>(evaluate(node->children[1]));

            double result =
                RandomService::number(
                    static_cast<int>(minimum),
                    static_cast<int>(maximum));

            environment->set(node->value, result);
            break;
        }

        case NodeType::LocalStorage:
        {
            if (node->children.empty())
                throw std::runtime_error(
                    "Local Storage requires a value.");

            environment->set(
                node->value,
                evaluate(node->children[0]));

            break;
        }

        case NodeType::EventHandler:
            registerEvent(node);
            break;

        case NodeType::PackageDeclaration:
        case NodeType::Import:
        case NodeType::Export:
            break;

        default:
            break;
    }
}

void Interpreter::executeBlock(
    const std::vector<AST>& nodes)
{
    for (const auto& node : nodes)
    {
        executeNode(node);

        if (returning ||
            breaking ||
            continuing)
        {
            break;
        }
    }
}

void Interpreter::executeIf(const AST& node)
{
    if (node->children.empty())
        return;

    if (isTruthy(evaluate(node->children[0])))
    {
        for (std::size_t i = 1; i < node->children.size(); ++i)
        {
            executeNode(node->children[i]);

            if (returning ||
                breaking ||
                continuing)
                break;
        }

        return;
    }

    for (std::size_t i = 1; i < node->children.size(); ++i)
    {
        const AST& branch = node->children[i];

        if (!branch)
            continue;

        if (branch->type == NodeType::ElseIf)
        {
            if (!branch->children.empty() &&
                isTruthy(evaluate(branch->children[0])))
            {
                for (std::size_t j = 1;
                     j < branch->children.size();
                     ++j)
                {
                    executeNode(branch->children[j]);

                    if (returning ||
                        breaking ||
                        continuing)
                        break;
                }

                return;
            }
        }
        else if (branch->type == NodeType::Else)
        {
            executeBlock(branch->children);
            return;
        }
    }
}

void Interpreter::executeWhile(const AST& node)
{
    if (node->children.empty())
        return;

    int safety = 0;

    while (isTruthy(evaluate(node->children[0])))
    {
        if (++safety > loopSafetyLimit)
        {
            throw std::runtime_error(
                "While loop exceeded the safety limit.");
        }

        breaking = false;
        continuing = false;

        for (std::size_t i = 1;
             i < node->children.size();
             ++i)
        {
            executeNode(node->children[i]);

            if (returning ||
                breaking ||
                continuing)
                break;
        }

        if (returning)
            return;

        if (breaking)
        {
            breaking = false;
            return;
        }

        if (continuing)
        {
            continuing = false;
            continue;
        }
    }
}

void Interpreter::executeFor(const AST& node)
{
    if (node->children.size() < 2)
        return;

    double start =
        std::get<double>(evaluate(node->children[0]));

    double end =
        std::get<double>(evaluate(node->children[1]));

    int safety = 0;

    const double step =
        start <= end ? 1.0 : -1.0;

    for (double i = start;
         step > 0 ? i <= end : i >= end;
         i += step)
    {
        if (++safety > loopSafetyLimit)
        {
            throw std::runtime_error(
                "For loop exceeded the safety limit.");
        }

        environment->set(node->value, i);

        breaking = false;
        continuing = false;

        for (std::size_t j = 2;
             j < node->children.size();
             ++j)
        {
            executeNode(node->children[j]);

            if (returning ||
                breaking ||
                continuing)
                break;
        }

        if (returning)
            return;

        if (breaking)
        {
            breaking = false;
            return;
        }

        if (continuing)
        {
            continuing = false;
            continue;
        }
    }
}

void Interpreter::registerFunction(const AST& node)
{
    FunctionDefinition function;

    for (const auto& child : node->children)
    {
        if (child->type == NodeType::Variable)
        {
            function.parameters.push_back(child->value);
        }
        else
        {
            function.body.push_back(child);
        }
    }

    functions[node->value] = function;
}

void Interpreter::registerEvent(const AST& node)
{
    EventSystem::on(
        node->value,
        [this, node]()
        {
            for (const auto& child : node->children)
                executeNode(child);
        });
}

RuntimeValue Interpreter::callFunction(
    const std::string& name,
    const std::vector<AST>& arguments)
{
    auto it = functions.find(name);

    if (it == functions.end())
    {
        throw std::runtime_error(
            "Function '" + name + "' is not defined.");
    }

    const FunctionDefinition& function = it->second;

    if (arguments.size() != function.parameters.size())
    {
        throw std::runtime_error(
            "Function '" + name +
            "' received the wrong number of arguments.");
    }

    auto previousEnvironment = environment;
    bool previousReturning = returning;
    RuntimeValue previousReturnValue = returnValue;

    environment =
        std::make_shared<Environment>(previousEnvironment);

    returning = false;
    returnValue = std::monostate{};

    for (std::size_t i = 0;
         i < function.parameters.size();
         ++i)
    {
        environment->set(
            function.parameters[i],
            evaluate(arguments[i]));
    }

    for (const auto& node : function.body)
    {
        executeNode(node);

        if (returning)
            break;
    }

    RuntimeValue result = returnValue;

    environment = previousEnvironment;
    returning = previousReturning;
    returnValue = previousReturnValue;

    return result;
}

RuntimeValue Interpreter::evaluate(
    const AST& node)
{
    if (!node)
        return std::monostate{};

    switch (node->type)
    {
        case NodeType::Literal:
            return parseLiteral(node->value);

        case NodeType::Variable:
            return environment->get(node->value);

        case NodeType::BinaryExpression:
            return evaluateBinary(node);

        case NodeType::FunctionCall:
            return callFunction(
                node->value,
                node->children);

        default:
            return std::monostate{};
    }
}

RuntimeValue Interpreter::evaluateBinary(
    const AST& node)
{
    if (node->children.size() < 2)
        throw std::runtime_error(
            "Binary expression requires two operands.");

    RuntimeValue left =
        evaluate(node->children[0]);

    RuntimeValue right =
        evaluate(node->children[1]);

    const std::string& op = node->value;

    if (op == "==")
        return valuesEqual(left, right);

    if (op == "And")
        return isTruthy(left) && isTruthy(right);

    if (op == "Or")
        return isTruthy(left) || isTruthy(right);

    if (op == "+")
    {
        if (std::holds_alternative<double>(left) &&
            std::holds_alternative<double>(right))
        {
            return std::get<double>(left) +
                   std::get<double>(right);
        }

        return valueToString(left) +
               valueToString(right);
    }

    if (op == "-" ||
        op == "*" ||
        op == "/" ||
        op == ">" ||
        op == "<" ||
        op == ">=" ||
        op == "<=")
    {
        if (!std::holds_alternative<double>(left) ||
            !std::holds_alternative<double>(right))
        {
            throw std::runtime_error(
                "Numeric operator '" + op +
                "' requires numbers.");
        }

        const double a = std::get<double>(left);
        const double b = std::get<double>(right);

        if (op == "-")
            return a - b;

        if (op == "*")
            return a * b;

        if (op == "/")
        {
            if (b == 0)
                throw std::runtime_error(
                    "Division by zero.");

            return a / b;
        }

        if (op == ">")
            return a > b;

        if (op == "<")
            return a < b;

        if (op == ">=")
            return a >= b;

        if (op == "<=")
            return a <= b;
    }

    throw std::runtime_error(
        "Unknown operator '" + op + "'.");
}

RuntimeValue Interpreter::parseLiteral(
    const std::string& value)
{
    if (value == "true")
        return true;

    if (value == "false")
        return false;

    if (value == "null")
        return std::monostate{};

    if (value.size() >= 2 &&
        value.front() == '"' &&
        value.back() == '"')
    {
        return value.substr(
            1,
            value.size() - 2);
    }

    try
    {
        std::size_t consumed = 0;
        double number = std::stod(value, &consumed);

        if (consumed == value.size())
            return number;
    }
    catch (...)
    {
    }

    return value;
}

std::shared_ptr<Environment>
Interpreter::getEnvironment() const
{
    return environment;
}


