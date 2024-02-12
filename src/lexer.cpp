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
Lexer::Lexer(const std::string &source) : source(source), currentPos(0), line(1), column(0) {}

// Get Next Token
Token Lexer::getNextToken()
{

    // Skip Whitespace and Layout Characters
    while (currentPos < source.length() && isLayout(source[currentPos]))
    {
        if (source[currentPos] == '\n')
        {
            line++;
            int temp = column;
            column = 0;
            currentPos++;
            return {TokenType::END_OF_LINE, "\\n", line - 1, temp + 1};
        }
            column++;
        currentPos++;
    }

    // Checks End of Source Code
    if (currentPos >= source.length())
    {
        return {TokenType::END_OF_FILE, "", line, column};
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
        column++;
        currentPos++;
        return {TokenType::PLUS, "+", line, column};
    case '-':
        column++;
        currentPos++;
        return {TokenType::MINUS, "-", line, column};
    case '*':
        column++;
        currentPos++;
        return {TokenType::MULTIPLY, "*", line, column};
    case '/':
        column++;
        currentPos++;

        // Handle Single Line Comments
        if (source[currentPos] == '/')
        {
            column++;
            currentPos++;
            while (currentPos < source.length() && source[currentPos] != '\n')
            {
                column++;
                currentPos++;
            }
            return getNextToken();
        }
        return {TokenType::DIVIDE, "/", line, column};
    case '%':
        column++;
        currentPos++;
        return {TokenType::MODULO, "%", line, column};
    case '(':
        column++;
        currentPos++;
        return {TokenType::LEFT_PAREN, "(", line, column};
    case ')':
        column++;
        currentPos++;
        return {TokenType::RIGHT_PAREN, ")", line, column};
    case '{':
        column++;
        currentPos++;
        return {TokenType::LEFT_BRACE, "{", line, column};
    case '}':
        column++;
        currentPos++;
        return {TokenType::RIGHT_BRACE, "}", line, column};
    case '=':
        column++;
        currentPos++;

        // Check for Equality Operator
        if (source[currentPos] == '=')
        {
            column++;
            currentPos++;
            return {TokenType::EQUAL, "==", line, column};
        }
        return {TokenType::EQUAL, "=", line, column};
    case '!':
        column++;
        currentPos++;

        // Check for Not Equal Operator
        if (source[currentPos] == '=')
        {
            column++;
            currentPos++;
            return {TokenType::NOT_EQUAL, "!=", line, column};
        }
        return {TokenType::NOT, "!", line, column};
    case '>':
        column++;
        currentPos++;

        // Check for Greater than or Equal Operator
        if (source[currentPos] == '=')
        {
            column++;
            currentPos++;
            return {TokenType::GREATER_THAN_EQUAL, ">=", line, column};
        }
        return {TokenType::GREATER_THAN, ">", line, column};
    case '<':
        column++;
        currentPos++;

        // Check for Less than or Equal Operator
        if (source[currentPos] == '=')
        {
            column++;
            currentPos++;
            return {TokenType::LESS_THAN_EQUAL, "<=", line, column};
        }
        else if (source[currentPos] == '<')
        {
            column++;
            currentPos++;
            return {TokenType::PAREN, "<<", line, column};
        }
        return {TokenType::LESS_THAN, "<", line, column};
    case '&':
        column++;
        currentPos++;

        // Checks for Logical AND
        if (source[currentPos] == '&')
        {
            column++;
            currentPos++;
            return {TokenType::AND, "&&", line, column};
        }
        return {TokenType::AND, "&", line, column};
    case '|':
        column++;
        currentPos++;

        // Checks for Logical OR
        if (source[currentPos] == '|')
        {
            column++;
            currentPos++;
            return {TokenType::OR, "||", line, column};
        }
        return {TokenType::OR, "|", line, column};
    case ';':
        column++;
        currentPos++;
        return {TokenType::SEMICOLON, ";", line, column};
    case ',':
        column++;
        currentPos++;
        return {TokenType::COMMA, ",", line, column};
    case ':':
        column++;
        currentPos++;
        return {TokenType::COLON, ":", line, column};
    case '.':
        column++;
        currentPos++;
        return {TokenType::DOT, ".", line, column};
    case '#':
        column++;
        currentPos++;

        // Handle Comments Starting With # For Python
        while (currentPos < source.length() && source[currentPos] != '\n')
        {
            column++;
            currentPos++;
        }
        return getNextToken();
    }

    // Tokenize Identifiers
    if (isIdentifierCharacter(source[currentPos]))
    {
        return getIdentifierToken();
    }

    // Tokenize String Literals
    if (source[currentPos] == '"')
    {
        return getStringToken();
    }

    // Handle Invalid Characters
    column++;
    currentPos++;
    return {TokenType::INVALID, string(1, source[currentPos - 1])};
}

// Tokenize Identifiers
bool Lexer::isIdentifierCharacter(char c){
    switch(c) {
        case '_':
        case '$':
            return true;
        default:
            return isalpha(c);
    }
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
        column++;
        currentPos++;
    }

    // Check for Floating Point
    if (source[currentPos] == '.')
    {
        value += source[currentPos];
        column++;
        currentPos++;

        // Check for Decimal
        if (!isdigit(source[currentPos]))
        {
            return {TokenType::INVALID, value, line, column};
        }

        // Get Decimal
        while (currentPos < source.length() && isdigit(source[currentPos]))
        {
            value += source[currentPos];
            column++;
            currentPos++;
        }
        return {TokenType::FLOAT, value, line, column};
    }
    return {TokenType::NUMBER, value, line, column};
}

// Tokenize Identifiers and Keywords
Token Lexer::getIdentifierToken()
{
    string value;
    while (currentPos < source.length() && (isalnum(source[currentPos]) || source[currentPos] == '_' || source[currentPos] == '$' || source[currentPos] == '.' || source[currentPos] == '!'))
    {
        value += source[currentPos];
        column++;
        currentPos++;
    }

    // Checks for Keywords
    if (value == "if")
    {
        return {TokenType::IF, value, line, column};
    }
    if (value == "else")
    {
        return {TokenType::ELSE, value, line, column};
    }
    if (value == "while")
    {
        return {TokenType::WHILE, value, line, column};
    }
    if (value == "var" || value == "let" || value == "const" || value == "int")
    {
        return {TokenType::VAR, value, line, column};
    }
    if (value == "print" || value == "println" || value == "println!" || value == "printf" || value == "echo" || value == "cout" || value == "log" || value == "console.log"  || value == "System.out.println") 
    {
        return {TokenType::PRINT, value, line, column};
    }
    if (value == "true")
    {
        return {TokenType::BOOLEAN, value, line, column};
    }
    if (value == "false")
    {
        return {TokenType::BOOLEAN, value, line, column};
    }
    return {TokenType::IDENTIFIER, value, line, column};
}

// Tokenize String Literals
Token Lexer::getStringToken()
{
    string value;
    column++;
    currentPos++;
    while (currentPos < source.length() && source[currentPos] != '"')
    {
        value += source[currentPos];
        column++;
        currentPos++;
    }
    column++;
    currentPos++;
    return {TokenType::STRING, value, line, column};
}

