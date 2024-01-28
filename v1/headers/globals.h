#include <stdlib.h>
#ifndef globals_h
#define globals_h

using namespace std;

enum TokenType {
    NUMBER, 
    FLOAT,
    BOOLEAN,
    IDENTIFIER,
    STRING,
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    MODULO,
    EQUAL,
    NOT_EQUAL,
    GREATER_THAN,
    LESS_THAN,
    GREATER_THAN_EQUAL,
    LESS_THAN_EQUAL,
    AND,
    OR,
    NOT,
    IF,
    ELSE,
    WHILE,
    VAR,
    DECLARE,
    PRINT,
    LEFT_PAREN,
    RIGHT_PAREN,
    LEFT_BRACE,
    RIGHT_BRACE,
    END_OF_FILE
};

struct Token {
    TokenType type;
    string value;
};

#endif /* globals_h */