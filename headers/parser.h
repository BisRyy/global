// Lexer.h
#include <string>
#include "globals.h"
#include "lexer.h"

#ifndef PARSE_H
#define PARSE_H

class Parser {
public:
    Parser(Lexer& lexer);
    int parse();
private:
    Lexer lexer;
    Token token;
    int parseStatement();
    int parseExpression();
    int parseLogicalExpression();
    int parseRelationalExpression();
    int parseAdditiveExpression();
    int parseTerm();
    int parseFactor();
};

#endif // PARSE_H
