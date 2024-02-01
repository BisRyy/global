#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <unordered_map>
#include "../headers/lexer.h"
#include "../headers/parser.h"

using namespace std;

void printToken(Token currentToken);

unordered_map<string, int> variables;

Parser::Parser(Lexer& lexer) : lexer(lexer) {}

int Parser::parse() {
    token = lexer.getNextToken();
    if (token.type == TokenType::END_OF_FILE) {
        // Empty program
        return 0;
    }
    int result =  parseStatement();
    return result;
}

int Parser::parseStatement(){
    if (token.type == TokenType::PRINT){
        token = lexer.getNextToken();
        if (token.type == TokenType::LEFT_PAREN || token.type == TokenType::PAREN){
            token = lexer.getNextToken();
            if (token.type == TokenType::STRING){
                string value = token.value;
                token = lexer.getNextToken();
                if (token.type == TokenType::RIGHT_PAREN || token.type == TokenType::PAREN){
                    cout << "PRINT: " << value << endl;
                    token = lexer.getNextToken();
                    return 0;
                } else {
                    // cerr << "Error: Invalid print statement" << endl;
                    return 0;
                }
            } else {
                int value = parseExpression();
                if (token.type == TokenType::RIGHT_PAREN || token.type == TokenType::PAREN){
                    cout << "PRINT: " << value << endl;
                    token = lexer.getNextToken();
                    return 0;
                } else {
                    // cerr << "Error: Invalid print statement" << endl;
                    return 0;
                }
            }
        } else {
            if (token.type == TokenType::STRING){
                string value = token.value;
                cout << "PRINT: " << value << endl;
                token = lexer.getNextToken();
            } else {
                int value = parseExpression();
                cout << "PRINT: " << value << endl;
                token = lexer.getNextToken();
            }
        }
    } else if (token.type == TokenType::VAR){
        token = lexer.getNextToken();
        if (token.type == TokenType::IDENTIFIER){
            string variableName = token.value;
            token = lexer.getNextToken();

            if (token.type == TokenType::EQUAL){
                token = lexer.getNextToken();

                if (variables.find(variableName) != variables.end()){
                    // cerr << "Warning: Variable '" << variableName << "' already declared" << endl;
                }

                int value = parseExpression();
                variables[variableName] = value;
                // cerr << "variable " << variableName << " declared with value " << value << endl; 
            } else {
                // cerr << "Error: Invalid variable declaration" << endl;
                return 0;
            }
        } else {
            // cerr << "Error: Invalid variable declaration" << endl;
            return 0;
        }
    } else if (token.type == TokenType::IDENTIFIER){
        string variableName = token.value;
        token = lexer.getNextToken();

        if (token.type == TokenType::EQUAL){
            token = lexer.getNextToken();

            if (variables.find(variableName) == variables.end()){
                // cerr << "Warning: Variable '" << variableName << "' not declared" << endl;
            }

            int value = parseExpression();
            variables[variableName] = value;
            // cerr << "variable " << variableName << " assigned value " << value << endl;
        } else {
            // cerr << "Error: Invalid variable assignment" << endl;
            return 0;
        }
    } else if (token.type == TokenType::IF){
        token = lexer.getNextToken();
        if (token.type == TokenType::LEFT_PAREN){
            token = lexer.getNextToken();
            int value = parseExpression();
            if (token.type == TokenType::RIGHT_PAREN){
                token = lexer.getNextToken();
                if (value){
                    parseStatement();
                } else {
                    while (token.type != TokenType::END_OF_FILE && token.type != TokenType::ELSE){
                        token = lexer.getNextToken();
                    }
                    if (token.type == TokenType::ELSE){
                        token = lexer.getNextToken();
                        parseStatement();
                    }
                }
            } else {
                // cerr << "Error: Invalid if statement" << endl;
                return 0;
            }
        } else {
            int value = parseExpression();
            if (value){
                parseStatement();
            } else {
                while (token.type != TokenType::END_OF_FILE && token.type != TokenType::ELSE){
                    token = lexer.getNextToken();
                }
                if (token.type == TokenType::ELSE){
                    token = lexer.getNextToken();
                    parseStatement();
                }
            }
            return 0;
        }
    } else {
        // cerr << "Error: Invalid statement" << endl;
        return 0;

    }
    return 0;
}

int Parser::parseExpression(){
    return parseLogicalExpression();
}

int Parser::parseLogicalExpression(){
    if (token.type == TokenType::NOT){
        token = lexer.getNextToken();
        return !parseLogicalExpression();
    } else {
        int result = parseRelationalExpression();
        while (token.type == TokenType::AND || token.type == TokenType::OR){
            if (token.type == TokenType::AND){
                token = lexer.getNextToken();
                int temp = parseRelationalExpression();
                result = result && temp;
            } else if (token.type == TokenType::OR){
                token = lexer.getNextToken();
                int temp = parseRelationalExpression();
                result = result || temp;
            }
        }
        return result;
    }
}

int Parser::parseRelationalExpression(){
    int result = parseAdditiveExpression();
    while (token.type == TokenType::LESS_THAN || token.type == TokenType::GREATER_THAN || token.type == TokenType::LESS_THAN_EQUAL || token.type == TokenType::GREATER_THAN_EQUAL || token.type == TokenType::EQUAL || token.type == TokenType::NOT_EQUAL){
        if (token.type == TokenType::LESS_THAN){
            token = lexer.getNextToken();
            result = result < parseAdditiveExpression();
        } else if (token.type == TokenType::GREATER_THAN){
            token = lexer.getNextToken();
            result = result > parseAdditiveExpression();
        } else if (token.type == TokenType::LESS_THAN_EQUAL){
            token = lexer.getNextToken();
            result = result <= parseAdditiveExpression();
        } else if (token.type == TokenType::GREATER_THAN_EQUAL){
            token = lexer.getNextToken();
            result = result >= parseAdditiveExpression();
        } else if (token.type == TokenType::EQUAL){
            token = lexer.getNextToken();
            result = result == parseAdditiveExpression();
        } else if (token.type == TokenType::NOT_EQUAL){
            token = lexer.getNextToken();
            result = result != parseAdditiveExpression();
        }
    }
    return result;
}

int Parser::parseAdditiveExpression(){
    int result = parseTerm();
    while (token.type == TokenType::PLUS || token.type == TokenType::MINUS){
        if (token.type == TokenType::PLUS){
            token = lexer.getNextToken();
            result += parseTerm();
        } else if (token.type == TokenType::MINUS){
            token = lexer.getNextToken();
            result -= parseTerm();
        }
    }
    return result;
}

int Parser::parseTerm(){
    int result = parseFactor();
    while (token.type == TokenType::MULTIPLY || token.type == TokenType::DIVIDE || token.type == TokenType::MODULO){
        if (token.type == TokenType::MULTIPLY){
            token = lexer.getNextToken();
            result *= parseFactor();
        } else if (token.type == TokenType::DIVIDE){
            token = lexer.getNextToken();
            int divisor = parseFactor();
            if (divisor != 0){
                result /= divisor;
            } else {
                // cerr << "Error: Division by zero" << endl;
                return 0;
            }
        } else if (token.type == TokenType::MODULO){
            token = lexer.getNextToken();
            int divisor = parseFactor();
            if (divisor != 0){
                result %= divisor;
            } else {
                // cerr << "Error: Modulo by zero" << endl;
                return 0;
            }
        }
    }
    return result;
}

int Parser::parseFactor(){
    if (token.type == TokenType::NUMBER){
        int value = stoi(token.value);
        token = lexer.getNextToken();
        return value;
    } else if (token.type == TokenType::IDENTIFIER){
        string variableName = token.value;
        token = lexer.getNextToken();
        if (variables.find(variableName) == variables.end()){
            // cerr << "Error: Variable '" << variableName << "' not declared" << endl;
            return 0;
        }
        return variables[variableName];
    } else if (token.type == TokenType::BOOLEAN){
        int value = token.value == "true" ? 1 : 0;
        token = lexer.getNextToken();
        return value;
    } else if (token.type == TokenType::STRING){

    }
    else if (token.type == TokenType::LEFT_PAREN){
        token = lexer.getNextToken();
        int value = parseExpression();
        if (token.type == TokenType::RIGHT_PAREN){
            token = lexer.getNextToken();
            return value;
        } else {
            // cerr << "Error: Invalid expression" << endl;
            return 0;
        }
    } else if (token.type == TokenType::FLOAT){
        float value = stof(token.value);
        token = lexer.getNextToken();
        return value;
    } else {
        // cerr << "Error: Invalid expression" << endl;
        return 0;
    }
    return 0;
}

// int main( int argc, char* argv[] ) { // take file name as parameter
//     if (argc != 2) {
//         // cerr << "Usage: " << argv[0] << " <filename>" << endl;
//         return 1;
//     }

//     ifstream file(argv[1]);
//     if (!file.is_open()) {
//         // cerr << "Error: Unable to open file '" << argv[1] << "'" << endl;
//         return 1;
//     }

//     string source;
//     string line;
//     while (getline(file, line)) {
//         Lexer lexer(line);
//         Parser parser(lexer);
//         int result = parser.parse();
//     }

//     return 0;
// }
