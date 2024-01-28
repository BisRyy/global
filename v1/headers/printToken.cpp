//
//  printToken.cpp
//  Lexical Analyzer
//

#include <stdio.h>
#include <iomanip>
#include <iostream>
#include "globals.h"

void printToken(Token currentToken){
    switch (currentToken.type) {
        case TokenType::NUMBER:
            cout << setw(20) << left << "NUMBER" << currentToken.value << endl;
            break;
        case TokenType::FLOAT:
            cout << setw(20) << left << "FLOAT" << currentToken.value << endl;
            break;
        case TokenType::BOOLEAN:
            cout << setw(20) << left << "BOOLEAN" << currentToken.value << endl;
            break;
        case TokenType::IDENTIFIER:
            cout << setw(20) << left << "IDENTIFIER" << currentToken.value << endl;
            break;
        case TokenType::STRING:
            cout << setw(20) << left << "STRING" << currentToken.value << endl;
            break;
        case TokenType::PLUS:
            cout << setw(20) << left << "PLUS" << currentToken.value << endl;
            break;
        case TokenType::MINUS:
            cout << setw(20) << left << "MINUS" << currentToken.value << endl;
            break;
        case TokenType::MULTIPLY:
            cout << setw(20) << left << "MULTIPLY" << currentToken.value << endl;
            break;
        case TokenType::DIVIDE:
            cout << setw(20) << left << "DIVIDE" << currentToken.value << endl;
            break;
        case TokenType::MODULO:
            cout << setw(20) << left << "MODULO" << currentToken.value << endl;
            break;
        case TokenType::EQUAL:
            cout << setw(20) << left << "EQUAL" << currentToken.value << endl;
            break;
        case TokenType::NOT_EQUAL:  
            cout << setw(20) << left << "NOT_EQUAL" << currentToken.value << endl;
            break;
        case TokenType::GREATER_THAN:
            cout << setw(20) << left << "GREATER_THAN" << currentToken.value << endl;
            break;
        case TokenType::LESS_THAN:
            cout << setw(20) << left << "LESS_THAN" << currentToken.value << endl;
            break;
        case TokenType::GREATER_THAN_EQUAL:
            cout << setw(20) << left << "GREATER_THAN_EQUAL" << currentToken.value << endl;
            break;
        case TokenType::LESS_THAN_EQUAL:
            cout << setw(20) << left << "LESS_THAN_EQUAL" << currentToken.value << endl;
            break;
        case TokenType::AND:
            cout << setw(20) << left << "AND" << currentToken.value << endl;
            break;
        case TokenType::OR:
            cout << setw(20) << left << "OR" << currentToken.value << endl;
            break;
        case TokenType::NOT:
            cout << setw(20) << left << "NOT" << currentToken.value << endl;
            break;
        case TokenType::IF:
            cout << setw(20) << left << "IF" << currentToken.value << endl;
            break;
        case TokenType::ELSE:
            cout << setw(20) << left << "ELSE" << currentToken.value << endl;
            break;
        case TokenType::WHILE:
            cout << setw(20) << left << "WHILE" << currentToken.value << endl;
            break;
        case TokenType::VAR:
            cout << setw(20) << left << "VAR" << currentToken.value << endl;
            break;
        case TokenType::DECLARE:
            cout << setw(20) << left << "DECLARE" << currentToken.value << endl;
            break;
        case TokenType::PRINT:
            cout << setw(20) << left << "PRINT" << currentToken.value << endl;
            break;
        case TokenType::LEFT_PAREN:
            cout << setw(20) << left << "LEFT_PAREN" << currentToken.value << endl;
            break;
        case TokenType::RIGHT_PAREN:
            cout << setw(20) << left << "RIGHT_PAREN" << currentToken.value << endl;
            break;
        case TokenType::LEFT_BRACE:
            cout << setw(20) << left << "LEFT_BRACE" << currentToken.value << endl;
            break;
        case TokenType::RIGHT_BRACE:
            cout << setw(20) << left << "RIGHT_BRACE" << currentToken.value << endl;
            break;
        case TokenType::END_OF_FILE:
            cout << setw(20) << left << "END_OF_FILE" << currentToken.value << endl;
            break;
        default:
            cout << setw(20) << left << "INVALID TOKEN" << endl;
            break;
    }
}


