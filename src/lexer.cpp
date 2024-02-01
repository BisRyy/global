// Lexer.cpp
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "../headers/lexer.h"

using namespace std;

// Print Current Token
void printToken(Token currentToken);

// Constructor for Lexer Class, Initializes Source Code and Current Position
Lexer::Lexer(const std::string &source) : source(source), currentPos(0) {}

// Get Next Token
Token Lexer::getNextToken()
{

    // Skip Whitespace and Layout Characters
    while (currentPos < source.length() && isLayout(source[currentPos]))
    {
        currentPos++;
    }

    // Checks End of Source Code
    if (currentPos >= source.length())
    {
        return {TokenType::END_OF_FILE, ""};
    }

    // Tokenize Numeric Literals
    if (isdigit(source[currentPos]))
    {
        return getIntegerToken();
    }

    // Tokenize Various Symbol and Operator
    switch (source[currentPos])
    {
    case '+':
        currentPos++;
        return {TokenType::PLUS, "+"};
    case '-':
        currentPos++;
        return {TokenType::MINUS, "-"};
    case '*':
        currentPos++;
        return {TokenType::MULTIPLY, "*"};
    case '/':
        currentPos++;

        // Handle Single Line Comments
        if (source[currentPos] == '/')
        {
            currentPos++;
            while (currentPos < source.length() && source[currentPos] != '\n')
            {
                currentPos++;
            }
            return getNextToken();
        }
        return {TokenType::DIVIDE, "/"};
    case '%':
        currentPos++;
        return {TokenType::MODULO, "%"};
    case '(':
        currentPos++;
        return {TokenType::LEFT_PAREN, "("};
    case ')':
        currentPos++;
        return {TokenType::RIGHT_PAREN, ")"};
    case '{':
        currentPos++;
        return {TokenType::LEFT_BRACE, "{"};
    case '}':
        currentPos++;
        return {TokenType::RIGHT_BRACE, "}"};
    case '=':
        currentPos++;

        // Check for Equality Operator
        if (source[currentPos] == '=')
        {
            currentPos++;
            return {TokenType::EQUAL, "=="};
        }
        return {TokenType::EQUAL, "="};
    case '!':
        currentPos++;

        // Check for Not Equal Operator
        if (source[currentPos] == '=')
        {
            currentPos++;
            return {TokenType::NOT_EQUAL, "!="};
        }
        return {TokenType::NOT, "!"};
    case '>':
        currentPos++;

        // Check for Greater than or Equal Operator
        if (source[currentPos] == '=')
        {
            currentPos++;
            return {TokenType::GREATER_THAN_EQUAL, ">="};
        }
        return {TokenType::GREATER_THAN, ">"};
    case '<':
        currentPos++;

        // Check for Less than or Equal Operator
        if (source[currentPos] == '=')
        {
            currentPos++;
            return {TokenType::LESS_THAN_EQUAL, "<="};
        }
        else if (source[currentPos] == '<')
        {
            currentPos++;
            return {TokenType::PAREN, "<<"};
        }
        return {TokenType::LESS_THAN, "<"};
    case '&':
        currentPos++;

        // Checks for Logical AND
        if (source[currentPos] == '&')
        {
            currentPos++;
            return {TokenType::AND, "&&"};
        }
        return {TokenType::AND, "&"};
    case '|':
        currentPos++;

        // Checks for Logical OR
        if (source[currentPos] == '|')
        {
            currentPos++;
            return {TokenType::OR, "||"};
        }
        return {TokenType::OR, "|"};
    case ';':
        currentPos++;
        return {TokenType::SEMICOLON, ";"};
    case ',':
        currentPos++;
        return {TokenType::COMMA, ","};
    case ':':
        currentPos++;
        return {TokenType::COLON, ":"};
    case '.':
        currentPos++;
        return {TokenType::DOT, "."};
    case '#':
        currentPos++;

        // Handle Comments Starting With # For Python
        while (currentPos < source.length() && source[currentPos] != '\n')
        {
            currentPos++;
        }
        return getNextToken();
    }

    // Tokenize Identifiers
    if (isalpha(source[currentPos]) || source[currentPos] == '_' || source[currentPos] == '$')
    {
        return getIdentifierToken();
    }

    // Tokenize String Literals
    if (source[currentPos] == '"')
    {
        return getStringToken();
    }

    // Handle Invalid Characters
    currentPos++;
    return {TokenType::INVALID, string(1, source[currentPos - 1])};
}

// Check If a Character is Layout Character
bool Lexer::isLayout(char c)
{
    return c == ' ' || c == '\t' || c == '\n';
}

// Tokenize Integer and Floating Points Literals
Token Lexer::getIntegerToken()
{
    string value;
    while (currentPos < source.length() && isdigit(source[currentPos]))
    {
        value += source[currentPos];
        currentPos++;
    }
    if (source[currentPos] == '.')
    {
        value += source[currentPos];
        currentPos++;
        while (currentPos < source.length() && isdigit(source[currentPos]))
        {
            value += source[currentPos];
            currentPos++;
        }
        return {TokenType::FLOAT, value};
    }
    return {TokenType::NUMBER, value};
}

// Tokenize Identifiers and Keywords
Token Lexer::getIdentifierToken()
{
    string value;
    while (currentPos < source.length() && (isalnum(source[currentPos]) || source[currentPos] == '_' || source[currentPos] == '$' || source[currentPos] == '.' || source[currentPos] == '!'))
    {
        value += source[currentPos];
        currentPos++;
    }

    // Checks for Keywords
    if (value == "if")
    {
        return {TokenType::IF, value};
    }
    if (value == "else")
    {
        return {TokenType::ELSE, value};
    }
    if (value == "while")
    {
        return {TokenType::WHILE, value};
    }
    if (value == "var" || value == "let" || value == "const" || value == "int")
    {
        return {TokenType::VAR, value};
    }
    if (value == "print" || value == "println" || value == "println!" || value == "printf" || value == "echo" || value == "cout" || value == "log" || value == "console.log"  || value == "System.out.println") 
    {
        return {TokenType::PRINT, value};
    }
    if (value == "true")
    {
        return {TokenType::BOOLEAN, value};
    }
    if (value == "false")
    {
        return {TokenType::BOOLEAN, value};
    }
    return {TokenType::IDENTIFIER, value};
}

// Tokenize String Literals
Token Lexer::getStringToken()
{
    string value;
    currentPos++;
    while (currentPos < source.length() && source[currentPos] != '"')
    {
        value += source[currentPos];
        currentPos++;
    }
    currentPos++;
    return {TokenType::STRING, value};
}

