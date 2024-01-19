#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <unordered_map>
#include <fstream>

using namespace std;

// Token types
enum class TokenType {
    INTEGER,
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    MODULO,
    EOF_TOKEN,
    LPAREN,
    RPAREN,
    VAR,
    CONST,
    DECLARE,
    IDENTIFIER,
    PRINT
};

// Token structure
struct Token {
    TokenType type;
    string value;
};

// Lexer: Breaks down the source code into tokens
class Lexer {
public:
    Lexer(const string& source) : source(source), currentPos(0) {}

    Token getNextToken() {
        while (currentPos < source.length() && isspace(source[currentPos])) {
            currentPos++;
        }

        if (currentPos >= source.length()) {
            return { TokenType::EOF_TOKEN, "" };
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
                return { TokenType::DIVIDE, "/" };
            case '%':
                currentPos++;
                return { TokenType::MODULO, "%" };
            case '(':
                currentPos++;
                return { TokenType::LPAREN, "(" };
            case ')':
                currentPos++;
                return { TokenType::RPAREN, ")" };
            case '=':
                currentPos++;
                return { TokenType::DECLARE, "=" };
        }

        if (isalpha(source[currentPos])) {
            return getIdentifierToken();
        }

        // Invalid token
        return { TokenType::EOF_TOKEN, "" };
    }

private:
    Token getIntegerToken() {
        string value;
        while (currentPos < source.length() && isdigit(source[currentPos])) {
            value += source[currentPos];
            currentPos++;
        }
        return { TokenType::INTEGER, value };
    }

    Token getIdentifierToken() {
        string value;
        while (currentPos < source.length() && (isalnum(source[currentPos]) || source[currentPos] == '_')) {
            value += source[currentPos];
            currentPos++;
        }

        if (value == "var") {
            return { TokenType::VAR, value };
        } else if (value == "print") {
            return { TokenType::PRINT, value };
        }

        return { TokenType::IDENTIFIER, value };
    }

    string source;
    size_t currentPos;
};

// Variable symbol table
unordered_map<string, int> variables;

// Parser: Analyzes the syntax and performs BODMAS operations
class Parser {
public:
    Parser(Lexer& lexer) : lexer(lexer) {}

    int parse() {
        Token token = lexer.getNextToken();
        if (token.type == TokenType::EOF_TOKEN) {
            // Empty program
            return 0;
        }
        int result = parseStatement(token);
        return result;
    }

private:
    int parseStatement(Token& token) {
        if (token.type == TokenType::PRINT) {
            token = lexer.getNextToken();  // Consume "print"
            int result = parseExpression(token);
            cout << result << endl;
            return result;
        } else if (token.type == TokenType::VAR) {
            token = lexer.getNextToken();  // Consume a variable name
            if (token.type == TokenType::IDENTIFIER) {
                string variableName = token.value;
                token = lexer.getNextToken();  // Consume "="

                if (token.type == TokenType::DECLARE) {
                    token = lexer.getNextToken();  // Consume a value

                    // check if the variable is already declared
                    if (variables.find(variableName) != variables.end()) {
                        cerr << "Error: Variable '" << variableName << "' already declared" << endl;
                        return 0;
                    }

                    int value = parseExpression(token);
                    variables[variableName] = value;
                } else {
                    cerr << "Error: Invalid variable declaration" << endl;
                    return 0;
                }
            } else {
                cerr << "Error: Invalid variable declaration" << endl;
                return 0;
            }
        } else if (token.type == TokenType::IDENTIFIER) {
            // Variable assignment
            string variableName = token.value;
            token = lexer.getNextToken();  // Consume '='

            if (token.type == TokenType::DECLARE) {
                token = lexer.getNextToken();  

                // check if the variable is already declared
                if (variables.find(variableName) == variables.end()) {
                    cerr << "Error: Variable '" << variableName << "' not declared" << endl;
                    return 0;
                }

                int value = parseExpression(token);
                variables[variableName] = value;

            } else if (token.type == TokenType::PLUS || token.type == TokenType::MINUS || token.type == TokenType::MULTIPLY || token.type == TokenType::DIVIDE || token.type == TokenType::MODULO) {
                token = lexer.getNextToken();  // Consume '='
                int value = parseExpression(token);
                return value + variables[variableName];

            }
            else {
                cerr << "Error: Invalid variable assignment" << endl;
                return 0;
            }

        } else {
            // Regular expression evaluation
            return parseExpression(token);
        }

        return 0;
    }

    int parseExpression(Token& token) {
        int result = parseTerm(token);

        while (token.type == TokenType::PLUS || token.type == TokenType::MINUS) {
            if (token.type == TokenType::PLUS) {
                token = lexer.getNextToken();  // Consume '+'
                result += parseTerm(token);
            } else if (token.type == TokenType::MINUS) {
                token = lexer.getNextToken();  // Consume '-'
                result -= parseTerm(token);
            }
        }

        return result;
    }

    int parseTerm(Token& token) {
        int result = parseFactor(token);

        while (token.type == TokenType::MULTIPLY || token.type == TokenType::DIVIDE || token.type == TokenType::MODULO) {
            if (token.type == TokenType::MULTIPLY) {
                token = lexer.getNextToken();  // Consume '*'
                result *= parseFactor(token);
            } else if (token.type == TokenType::DIVIDE) {
                token = lexer.getNextToken();  // Consume '/'
                int divisor = parseFactor(token);
                if (divisor != 0) {
                    result /= divisor;
                } else {
                    cerr << "Error: Division by zero" << endl;
                    return 0;
                }
            } else if (token.type == TokenType::MODULO) {
                token = lexer.getNextToken();  // Consume '%'
                int divisor = parseFactor(token);
                if (divisor != 0) {
                    result %= divisor;
                } else {
                    cerr << "Error: Modulo by zero" << endl;
                    return 0;
                }
            }
        }

        return result;
    }

    int parseFactor(Token& token) {
        if (token.type == TokenType::INTEGER) {
            int value = stoi(token.value);
            token = lexer.getNextToken();  // Consume variable
            return value;
        } else if (token.type == TokenType::IDENTIFIER) {
            string variableName = token.value;
            token = lexer.getNextToken();  // Consume variable
            
            if (variables.find(variableName) != variables.end()) {
                return variables[variableName];
            } else {
                cerr << "Error: Variable '" << variableName << "' not found" << endl;
                return 0;
            }

        } else if (token.type == TokenType::LPAREN) {
            token = lexer.getNextToken();  // Consume '('
            int result = parseExpression(token);
            if (token.type == TokenType::RPAREN) {
                token = lexer.getNextToken();  // Consume ')'
                return result;
            } else {
                cerr << "Error: Unmatched parenthesis" << endl;
                return 0;
            }
        }

        // Invalid factor
        cerr << "Error: Invalid factor" << token.value << endl;
        return 0;
    }

    Lexer& lexer;
};

int main( int argc, char* argv[] ) { // take file name as parameter
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }

    ifstream file(argv[1]);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file '" << argv[1] << "'" << endl;
        return 1;
    }

    string source;
    string line;
    while (getline(file, line)) {
        Lexer lexer(line);
        Parser parser(lexer);
        int result = parser.parse();
    }
    

    return 0;
}
