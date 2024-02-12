// Lexer.h
#include <string>
#include "globals.h"
#include "lexer.h"

#ifndef PARSE_H
#define PARSE_H

class Parser {
public:
    Parser(Lexer& lexer);
    Parser(Lexer& lexer, bool error, bool warning, bool log);
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
    bool showError, showWarning, showLog;
};

#endif // PARSE_H
