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
    PAREN,
    LEFT_BRACE,
    RIGHT_BRACE,
    SEMICOLON,
    COLON,
    COMMA,
    DOT,
    INVALID,
    END_OF_LINE,
    END_OF_FILE
};

struct Token {
    TokenType type;
    string value;
    int line = 0;
    int column = 0;
    
    Token() {
        type = INVALID;
        value = "";
        line = 0;
        column = 0;
    }

    Token(TokenType type, string value) {
        this->type = type;
        this->value = value;
        this->line = 0;
        this->column = 0;
    }
    
    Token(TokenType type, string value, int line, int column) {
        this->type = type;
        this->value = value;
        this->line = line;
        this->column = column;
    }  
};

#endif /* globals_h */