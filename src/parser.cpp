#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <unordered_map>
#include "../headers/lexer.h"
#include "../headers/parser.h"
#include "../headers/error.h"

using namespace std;

// Print Current Token
void printToken(Token currentToken);

// Global Unordered_map to Store Variable Values
unordered_map<string, int> variables;

Parser::Parser(Lexer &lexer) : lexer(lexer) {}

// Start Parsing Process
int Parser::parse()
{
    token = lexer.getNextToken();
    if (token.type == TokenType::END_OF_FILE)
    {
        // Empty program
        return 0;
    }
    int result = parseStatement();
    return result;
}

// Parse Statements
int Parser::parseStatement()
{
    // Implementation for Print Statement
    if (token.type == TokenType::PRINT)
    {
        token = lexer.getNextToken();
        if (token.type == TokenType::LEFT_PAREN || token.type == TokenType::PAREN)
        {
            // Handle Print Statement with Expression or String
            token = lexer.getNextToken();
            if (token.type == TokenType::STRING)
            {
                string value = token.value;
                token = lexer.getNextToken();
                if (token.type == TokenType::RIGHT_PAREN || token.type == TokenType::PAREN)
                {
                    cout << "PRINT: " << value << endl;
                    token = lexer.getNextToken();
                    return 0;
                }
                else
                {
                    // cerr << "Error: Invalid print statement" << endl;
                    return 0;
                }
            }
            else
            {
                // Parse and Print Expression Value
                int value = parseExpression();
                if (token.type == TokenType::RIGHT_PAREN || token.type == TokenType::PAREN)
                {
                    cout << "PRINT: " << value << endl;
                    token = lexer.getNextToken();
                    return 0;
                }
                else
                {
                    // cerr << "Error: Invalid print statement" << endl;
                    return 0;
                }
            }
        }
        else
        {
            // Handle Print Statement Without Parentheses
            if (token.type == TokenType::STRING)
            {
                string value = token.value;
                cout << value << endl;
                token = lexer.getNextToken();
            }
            else
            {
                int value = parseExpression();
                cout << value << endl;
                token = lexer.getNextToken();
            }
        }
    }

    // Implementation for Var Statement
    else if (token.type == TokenType::VAR)
    {
        token = lexer.getNextToken();
        if (token.type == TokenType::IDENTIFIER)
        {
            // Parse Variable Declaration and Assignment
            string variableName = token.value;
            token = lexer.getNextToken();

            if (token.type == TokenType::EQUAL)
            {
                token = lexer.getNextToken();

                // Check if Variable is Already Declared
                if (variables.find(variableName) != variables.end())
                {
                    // cerr << "Warning: Variable '" << variableName << "' already declared" << endl;
                }

                // Parse and Assign Value to Variable
                int value = parseExpression();
                variables[variableName] = value;
                // cerr << "variable " << variableName << " declared with value " << value << endl;
            }
            else
            {
                // cerr << "Error: Invalid variable declaration" << endl;
                return 0;
            }
        }
        else
        {
            // cerr << "Error: Invalid variable declaration" << endl;
            return 0;
        }
    }
    // Implementation for Variable Assignment Statement
    else if (token.type == TokenType::IDENTIFIER)
    {
        string variableName = token.value;
        token = lexer.getNextToken();

        if (token.type == TokenType::EQUAL)
        {
            token = lexer.getNextToken();

            // Check if Variable is Declared
            if (variables.find(variableName) == variables.end())
            {
                // cerr << "Warning: Variable '" << variableName << "' not declared" << endl;
            }

            // Parse and Assign Value to the Variable
            int value = parseExpression();
            variables[variableName] = value;
            // cerr << "variable " << variableName << " assigned value " << value << endl;
        }
        else
        {
            // cerr << "Error: Invalid variable assignment" << endl;
            return 0;
        }
    }
    // Implementation for If Statment
    else if (token.type == TokenType::IF)
    {
        token = lexer.getNextToken();
        if (token.type == TokenType::LEFT_PAREN)
        {
            token = lexer.getNextToken();
            int value = parseExpression();
            if (token.type == TokenType::RIGHT_PAREN)
            {
                token = lexer.getNextToken();
                if (value)
                {
                    // Parse Statements Inside the If Block
                    parseStatement();
                }
                else
                {
                    // Skip to Else or EOF
                    while (token.type != TokenType::END_OF_FILE && token.type != TokenType::ELSE)
                    {
                        token = lexer.getNextToken();
                    }
                    if (token.type == TokenType::ELSE)
                    {
                        token = lexer.getNextToken();
                        // Parse Statements inside Else Block
                        parseStatement();
                    }
                }
            }
            else
            {
                // cerr << "Error: Invalid if statement" << endl;
                return 0;
            }
        }
        else
        {
            int value = parseExpression();
            if (value)
            {
                // Parse Statements Inside the IF Block
                parseStatement();
            }
            else
            {
                // Skip to Else or EOF
                while (token.type != TokenType::END_OF_FILE && token.type != TokenType::ELSE)
                {
                    token = lexer.getNextToken();
                }
                if (token.type == TokenType::ELSE)
                {
                    token = lexer.getNextToken();
                    parseStatement();
                }
            }
            return 0;
        }
    }
    else
    {
        // cerr << "Error: Invalid statement" << endl;
        return 0;
    }
    return 0;
}

// Parse Expressions
int Parser::parseExpression()
{
    return parseLogicalExpression();
}

// Parse Logical Expressions
int Parser::parseLogicalExpression()
{
    if (token.type == TokenType::NOT)
    {
        token = lexer.getNextToken();
        return !parseLogicalExpression();
    }
    else
    {
        int result = parseRelationalExpression();
        while (token.type == TokenType::AND || token.type == TokenType::OR)
        {
            if (token.type == TokenType::AND)
            {
                token = lexer.getNextToken();
                int temp = parseRelationalExpression();
                result = result && temp;
            }
            else if (token.type == TokenType::OR)
            {
                token = lexer.getNextToken();
                int temp = parseRelationalExpression();
                result = result || temp;
            }
        }
        return result;
    }
}

// Parse Relational Expressions
int Parser::parseRelationalExpression()
{
    int result = parseAdditiveExpression();
    while (token.type == TokenType::LESS_THAN || token.type == TokenType::GREATER_THAN || token.type == TokenType::LESS_THAN_EQUAL || token.type == TokenType::GREATER_THAN_EQUAL || token.type == TokenType::EQUAL || token.type == TokenType::NOT_EQUAL)
    {
        if (token.type == TokenType::LESS_THAN)
        {
            token = lexer.getNextToken();
            result = result < parseAdditiveExpression();
        }
        else if (token.type == TokenType::GREATER_THAN)
        {
            token = lexer.getNextToken();
            result = result > parseAdditiveExpression();
        }
        else if (token.type == TokenType::LESS_THAN_EQUAL)
        {
            token = lexer.getNextToken();
            result = result <= parseAdditiveExpression();
        }
        else if (token.type == TokenType::GREATER_THAN_EQUAL)
        {
            token = lexer.getNextToken();
            result = result >= parseAdditiveExpression();
        }
        else if (token.type == TokenType::EQUAL)
        {
            token = lexer.getNextToken();
            result = result == parseAdditiveExpression();
        }
        else if (token.type == TokenType::NOT_EQUAL)
        {
            token = lexer.getNextToken();
            result = result != parseAdditiveExpression();
        }
    }
    return result;
}

// Parse Additive Expressions
int Parser::parseAdditiveExpression()
{
    int result = parseTerm();
    while (token.type == TokenType::PLUS || token.type == TokenType::MINUS)
    {
        if (token.type == TokenType::PLUS)
        {
            token = lexer.getNextToken();
            result += parseTerm();
        }
        else if (token.type == TokenType::MINUS)
        {
            token = lexer.getNextToken();
            result -= parseTerm();
        }
    }
    return result;
}

// Parse Term Expressions
int Parser::parseTerm()
{
    int result = parseFactor();
    while (token.type == TokenType::MULTIPLY || token.type == TokenType::DIVIDE || token.type == TokenType::MODULO)
    {
        if (token.type == TokenType::MULTIPLY)
        {
            token = lexer.getNextToken();
            result *= parseFactor();
        }
        else if (token.type == TokenType::DIVIDE)
        {
            token = lexer.getNextToken();
            int divisor = parseFactor();
            if (divisor != 0)
            {
                result /= divisor;
            }
            else
            {
                // cerr << "Error: Division by zero" << endl;
                return 0;
            }
        }
        else if (token.type == TokenType::MODULO)
        {
            token = lexer.getNextToken();
            int divisor = parseFactor();
            if (divisor != 0)
            {
                result %= divisor;
            }
            else
            {
                // cerr << "Error: Modulo by zero" << endl;
                return 0;
            }
        }
    }
    return result;
}

// Parse Factor Expressions
int Parser::parseFactor()
{
    if (token.type == TokenType::NUMBER)
    {
        // Parse and Return Integer Value
        int value = stoi(token.value);
        token = lexer.getNextToken();
        return value;
    }
    else if (token.type == TokenType::IDENTIFIER)
    {
        // Parse and Return Value of a Variable
        string variableName = token.value;
        token = lexer.getNextToken();
        if (variables.find(variableName) == variables.end())
        {
            // cerr << "Error: Variable '" << variableName << "' not declared" << endl;
            return 0;
        }
        return variables[variableName];
    }
    else if (token.type == TokenType::BOOLEAN)
    {
        // Parse and Return Boolean Value
        int value = token.value == "true" ? 1 : 0;
        token = lexer.getNextToken();
        return value;
    }
    else if (token.type == TokenType::STRING)
    {
        // Implementation for String Handling
    }
    else if (token.type == TokenType::LEFT_PAREN)
    {
        // Parse Expression Inside Parenthesis
        token = lexer.getNextToken();
        int value = parseExpression();
        if (token.type == TokenType::RIGHT_PAREN)
        {
            token = lexer.getNextToken();
            return value;
        }
        else
        {
            // cerr << "Error: Invalid expression" << endl;
            return 0;
        }
    }
    else if (token.type == TokenType::FLOAT)
    {
        // Parse and Return Float Value
        float value = stof(token.value);
        token = lexer.getNextToken();
        return value;
    }
    else
    {
        // cerr << "Error: Invalid expression" << endl;
        return 0;
    }
    return 0;
}
