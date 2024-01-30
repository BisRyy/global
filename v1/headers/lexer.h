// Lexer.h
#include <string>
#include "globals.h"

#ifndef LEXEX_H
#define LEXEX_H

class Lexer {
public:
    Lexer(const std::string& source);

    Token getNextToken();

private:
    bool isLayout(char c);
    Token getIntegerToken();
    Token getIdentifierToken();
    Token getStringToken();

    std::string source;
    int currentPos;
};

#endif // LEXEX_H
