// Lexer.cpp
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "../headers/lexer.h"


using namespace std;

void printToken(Token currentToken);
Lexer::Lexer(const std::string& source) : source(source), currentPos(0) {}

Token Lexer::getNextToken() {

    while (currentPos < source.length() && isLayout(source[currentPos])) {
        currentPos++;
    }

    if (currentPos >= source.length()) {
        return { TokenType::END_OF_FILE, "" };
    }

    if (isdigit(source[currentPos])) {
        return getIntegerToken();
    }

    switch(source[currentPos]) {
        case '+':
            currentPos++;
            return { TokenType::PLUS, "+" };
        case '-':
            currentPos++;
            return { TokenType::MINUS, "-" };
        case '*':
            currentPos++;
            return { TokenType::MULTIPLY, "*" };
        case '/':
            currentPos++;
            if (source[currentPos] == '/') {
                currentPos++;
                while (currentPos < source.length() && source[currentPos] != '\n') {
                    currentPos++;
                }
                return getNextToken();
            }
            return { TokenType::DIVIDE, "/" };
        case '%':
            currentPos++;
            return { TokenType::MODULO, "%" };
        case '(':
            currentPos++;
            return { TokenType::LEFT_PAREN, "(" };
        case ')':
            currentPos++;
            return { TokenType::RIGHT_PAREN, ")" };
        case '{':
            currentPos++;
            return { TokenType::LEFT_BRACE, "{" };
        case '}':
            currentPos++;
            return { TokenType::RIGHT_BRACE, "}" };
        case '=':
            currentPos++;
            if (source[currentPos] == '=') {
                currentPos++;
                return { TokenType::EQUAL, "==" };
            }
            return { TokenType::EQUAL, "=" };
        case '!':
            currentPos++;
            if (source[currentPos] == '=') {
                currentPos++;
                return { TokenType::NOT_EQUAL, "!=" };
            }
            return { TokenType::NOT, "!" };
        case '>':
            currentPos++;
            if (source[currentPos] == '=') {
                currentPos++;
                return { TokenType::GREATER_THAN_EQUAL, ">=" };
            }
            return { TokenType::GREATER_THAN, ">" };
        case '<':
            currentPos++;
            if (source[currentPos] == '=') {
                currentPos++;
                return { TokenType::LESS_THAN_EQUAL, "<=" };
            }else if (source[currentPos] == '<') {
                currentPos++;
                return { TokenType::PAREN, "<<" };
            }
            return { TokenType::LESS_THAN, "<" };
        case '&':
            currentPos++;
            if (source[currentPos] == '&') {
                currentPos++;
                return { TokenType::AND, "&&" };
            }
            return { TokenType::AND, "&" };
        case '|':
            currentPos++;
            if (source[currentPos] == '|') {
                currentPos++;
                return { TokenType::OR, "||" };
            }
            return { TokenType::OR, "|" };
        case ';':
            currentPos++;
            return { TokenType::SEMICOLON, ";" };
        case ',':
            currentPos++;
            return { TokenType::COMMA, "," };
        case ':':
            currentPos++;
            return { TokenType::COLON, ":" };
        case '.':
            currentPos++;
            return { TokenType::DOT, "." };
        case '#':
            currentPos++;
            while (currentPos < source.length() && source[currentPos] != '\n') {
                currentPos++;
            }
            return getNextToken();
    }

    if (isalpha(source[currentPos]) || source[currentPos] == '_' || source[currentPos] == '$') {
        return getIdentifierToken();
    }

    if (source[currentPos] == '"') {
        return getStringToken();
    }
    
    currentPos++;
    return { TokenType::INVALID, string(1, source[currentPos-1]) };

}

bool Lexer::isLayout(char c) {
    return c == ' ' || c == '\t' || c == '\n';
}

Token Lexer::getIntegerToken() {
    string value;
    while (currentPos < source.length() && isdigit(source[currentPos])) {
        value += source[currentPos];
        currentPos++;
    }
    if (source[currentPos] == '.') {
        value += source[currentPos];
        currentPos++;
        while (currentPos < source.length() && isdigit(source[currentPos])) {
            value += source[currentPos];
            currentPos++;
        }
        return { TokenType::FLOAT, value };
    }
    return { TokenType::NUMBER, value };
}

Token Lexer::getIdentifierToken() {
    string value;
    while (currentPos < source.length() && (isalnum(source[currentPos]) || source[currentPos] == '_' || source[currentPos] == '$' || source[currentPos] == '.' || source[currentPos] == '!')) {
        value += source[currentPos];
        currentPos++;
    }

    if (value == "if") {
        return { TokenType::IF, value };
    }
    if (value == "else") {
        return { TokenType::ELSE, value };
    }
    if (value == "while") {
        return { TokenType::WHILE, value };
    }
    if (value == "var" || value == "let" || value == "const" || value == "int") {
        return { TokenType::VAR, value };
    }
    if (value == "print" || value == "println" || value == "println!" || value == "printf" || value == "echo" || value == "cout" || value == "log" || value == "console.log") {
        return { TokenType::PRINT, value };
    }
    if (value == "true") {
        return { TokenType::BOOLEAN, value };
    }
    if (value == "false") {
        return { TokenType::BOOLEAN, value };
    }
    return { TokenType::IDENTIFIER, value };
}

Token Lexer::getStringToken() {
    string value;
    currentPos++;
    while (currentPos < source.length() && source[currentPos] != '"') {
        value += source[currentPos];
        currentPos++;
    }
    currentPos++;
    return { TokenType::STRING, value };
}

