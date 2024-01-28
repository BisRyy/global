
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "headers/globals.h"


using namespace std;

void printToken(Token currentToken);

class Lexer {
    public:
        Lexer(const string& source) : source(source), currentPos(0) {}

        Token getNextToken() {
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
            }

            if (isalpha(source[currentPos])) {
                return getIdentifierToken();
            }

            if (source[currentPos] == '"') {
                return getStringToken();
            }

            // Invalid token
            cout << "INVALID TOKEN" << endl;
            return { TokenType::END_OF_FILE, "" };

        }

    private:
        bool isLayout(char c) {
            return c == ' ' || c == '\t' || c == '\n';
        }

        Token getIntegerToken() {
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

        Token getIdentifierToken() {
            string value;
            while (currentPos < source.length() && (isalnum(source[currentPos]) || source[currentPos] == '_')) {
                value += source[currentPos];
                currentPos++;
            }
            if (value == "true" || value == "false") {
                return { TokenType::BOOLEAN, value };
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
            if (value == "var") {
                return { TokenType::VAR, value };
            }
            if (value == "print") {
                return { TokenType::PRINT, value };
            }
            if (value == "declare") {
                return { TokenType::DECLARE, value };
            }
            return { TokenType::IDENTIFIER, value };
        }

        Token getStringToken() {
            string value;
            currentPos++;
            while (currentPos < source.length() && source[currentPos] != '"') {
                value += source[currentPos];
                currentPos++;
            }
            currentPos++;
            return { TokenType::STRING, value };
        }

        string source;
        int currentPos;
};

int main( int argc, char *argv[] ) {
    // read file
    ifstream file(argv[1]);
    string source((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());

    // print the source code
    // cout << source << endl;
    cout << endl;

    // tokenize the source code
    Lexer lexer(source);
    Token currentToken = lexer.getNextToken();
    while (currentToken.type != TokenType::END_OF_FILE) {
        printToken(currentToken);
        currentToken = lexer.getNextToken();
    }
}
