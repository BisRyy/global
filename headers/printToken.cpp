#include <stdio.h>
#include <iomanip>
#include <iostream>
#include "globals.h"

void printToken(Token currentToken){
    switch (currentToken.type) {
        case TokenType::NUMBER:
            cout << setw(12) << left << "NUMBER" << setw(15) << left << currentToken.value << " LINE: "<< currentToken.line << " COLUMN: "<<currentToken.column << endl;
            break;
        case TokenType::FLOAT:
            cout << setw(12) << left << "FLOAT" << setw(15) << left << currentToken.value << " LINE: "<< currentToken.line << " COLUMN: "<<currentToken.column << endl;
            break;
        case TokenType::BOOLEAN:
            cout << setw(12) << left << "BOOLEAN" << setw(15) << left << currentToken.value << " LINE: "<< currentToken.line << " COLUMN: "<<currentToken.column << endl;
            break;
        case TokenType::IDENTIFIER:
            cout << setw(12) << left << "IDENTIFIER" << setw(15) << left << currentToken.value << " LINE: "<< currentToken.line << " COLUMN: "<<currentToken.column << endl;
            break;
        case TokenType::STRING:
            cout << setw(12) << left << "STRING" << setw(15) << left << currentToken.value << " LINE: "<< currentToken.line << " COLUMN: "<<currentToken.column << endl;
            break;
        case TokenType::PLUS:
            cout << setw(12) << left << "PLUS" << setw(15) << left << currentToken.value << " LINE: "<< currentToken.line << " COLUMN: "<<currentToken.column << endl;
            break;
        case TokenType::MINUS:
            cout << setw(12) << left << "MINUS" << setw(15) << left << currentToken.value << " LINE: "<< currentToken.line << " COLUMN: "<<currentToken.column << endl;
            break;
        case TokenType::MULTIPLY:
            cout << setw(12) << left << "MULTIPLY" << setw(15) << left << currentToken.value << " LINE: "<< currentToken.line << " COLUMN: "<<currentToken.column << endl;
            break;
        case TokenType::DIVIDE:
            cout << setw(12) << left << "DIVIDE" << setw(15) << left << currentToken.value << " LINE: "<< currentToken.line << " COLUMN: "<<currentToken.column << endl;
            break;
        case TokenType::MODULO:
            cout << setw(12) << left << "MODULO" << setw(15) << left << currentToken.value << " LINE: "<< currentToken.line << " COLUMN: "<<currentToken.column << endl;
            break;
        case TokenType::EQUAL:
            cout << setw(12) << left << "EQUAL" << setw(15) << left << currentToken.value << " LINE: "<< currentToken.line << " COLUMN: "<<currentToken.column << endl;
            break;
        case TokenType::NOT_EQUAL:  
            cout << setw(12) << left << "NOT_EQUAL" << setw(15) << left << currentToken.value << " LINE: "<< currentToken.line << " COLUMN: "<<currentToken.column << endl;
            break;
        case TokenType::GREATER_THAN:
            cout << setw(12) << left << "GREATER_THAN" << setw(15) << left << currentToken.value << " LINE: "<< currentToken.line << " COLUMN: "<<currentToken.column << endl;
            break;
        case TokenType::LESS_THAN:
            cout << setw(12) << left << "LESS_THAN" << setw(15) << left << currentToken.value << " LINE: "<< currentToken.line << " COLUMN: "<<currentToken.column << endl;
            break;
        case TokenType::GREATER_THAN_EQUAL:
            cout << setw(12) << left << "GREATER_THAN_EQUAL" << setw(15) << left << currentToken.value << " LINE: "<< currentToken.line << " COLUMN: "<<currentToken.column << endl;
            break;
        case TokenType::LESS_THAN_EQUAL:
            cout << setw(12) << left << "LESS_THAN_EQUAL" << setw(15) << left << currentToken.value << " LINE: "<< currentToken.line << " COLUMN: "<<currentToken.column << endl;
            break;
        case TokenType::AND:
            cout << setw(12) << left << "AND" << setw(15) << left << currentToken.value << " LINE: "<< currentToken.line << " COLUMN: "<<currentToken.column << endl;
            break;
        case TokenType::OR:
            cout << setw(12) << left << "OR" << setw(15) << left << currentToken.value << " LINE: "<< currentToken.line << " COLUMN: "<<currentToken.column << endl;
            break;
        case TokenType::NOT:
            cout << setw(12) << left << "NOT" << setw(15) << left << currentToken.value << " LINE: "<< currentToken.line << " COLUMN: "<<currentToken.column << endl;
            break;
        case TokenType::IF:
            cout << setw(12) << left << "IF" << setw(15) << left << currentToken.value << " LINE: "<< currentToken.line << " COLUMN: "<<currentToken.column << endl;
            break;
        case TokenType::ELSE:
            cout << setw(12) << left << "ELSE" << setw(15) << left << currentToken.value << " LINE: "<< currentToken.line << " COLUMN: "<<currentToken.column << endl;
            break;
        case TokenType::WHILE:
            cout << setw(12) << left << "WHILE" << setw(15) << left << currentToken.value << " LINE: "<< currentToken.line << " COLUMN: "<<currentToken.column << endl;
            break;
        case TokenType::VAR:
            cout << setw(12) << left << "VAR" << setw(15) << left << currentToken.value << " LINE: "<< currentToken.line << " COLUMN: "<<currentToken.column << endl;
            break;
        case TokenType::DECLARE:
            cout << setw(12) << left << "DECLARE" << setw(15) << left << currentToken.value << " LINE: "<< currentToken.line << " COLUMN: "<<currentToken.column << endl;
            break;
        case TokenType::PRINT:
            cout << setw(12) << left << "PRINT" << setw(15) << left << currentToken.value << " LINE: "<< currentToken.line << " COLUMN: "<<currentToken.column << endl;
            break;
        case TokenType::LEFT_PAREN:
            cout << setw(12) << left << "LEFT_PAREN" << setw(15) << left << currentToken.value << " LINE: "<< currentToken.line << " COLUMN: "<<currentToken.column << endl;
            break;
        case TokenType::RIGHT_PAREN:
            cout << setw(12) << left << "RIGHT_PAREN" << setw(15) << left << currentToken.value << " LINE: "<< currentToken.line << " COLUMN: "<<currentToken.column << endl;
            break;
        case TokenType::LEFT_BRACE:
            cout << setw(12) << left << "LEFT_BRACE" << setw(15) << left << currentToken.value << " LINE: "<< currentToken.line << " COLUMN: "<<currentToken.column << endl;
            break;
        case TokenType::RIGHT_BRACE:
            cout << setw(12) << left << "RIGHT_BRACE" << setw(15) << left << currentToken.value << " LINE: "<< currentToken.line << " COLUMN: "<<currentToken.column << endl;
            break;
        case TokenType::END_OF_FILE:
            cout << setw(12) << left << "END_OF_FILE" << setw(15) << left << currentToken.value << " LINE: "<< currentToken.line << " COLUMN: "<<currentToken.column << endl;
            break;
        case TokenType::SEMICOLON:
            cout << setw(12) << left << "SEMICOLON" << setw(15) << left << currentToken.value << " LINE: "<< currentToken.line << " COLUMN: "<<currentToken.column << endl;
            break;
        case TokenType::COLON:
            cout << setw(12) << left << "COLON" << setw(15) << left << currentToken.value << " LINE: "<< currentToken.line << " COLUMN: "<<currentToken.column << endl;
            break;
        case TokenType::COMMA:
            cout << setw(12) << left << "COMMA" << setw(15) << left << currentToken.value << " LINE: "<< currentToken.line << " COLUMN: "<<currentToken.column << endl;
            break;
        case TokenType::DOT:
            cout << setw(12) << left << "DOT" << setw(15) << left << currentToken.value << " LINE: "<< currentToken.line << " COLUMN: "<<currentToken.column << endl;
            break;
        case TokenType::END_OF_LINE:
            cout << setw(12) << left << "END_OF_LINE" << setw(15) << left << currentToken.value << " LINE: "<< currentToken.line << " COLUMN: "<<currentToken.column << endl << endl;
            break;
        default:
            cerr << "\033[1;31m";
            cerr << setw(12) << left << "INVALID TOKEN DETECTED: ";
            cerr << "\033[0m";
            cerr << setw(15) << left << currentToken.value << " LINE: "<< currentToken.line << " COLUMN: "<<currentToken.column << endl;
            break;
    }
}


