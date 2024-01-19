#include <iostream>
#include <vector>
#include <string>
#include <cctype>

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
    RPAREN
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

    string source;
    size_t currentPos;
};

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

        int result = parseExpression(token);
        return result;
    }

private:
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
            token = lexer.getNextToken();  // Consume integer
            return value;
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
        cerr << "Error: Invalid factor" << endl;
        return 0;
    }

    Lexer& lexer;
};

int main() {
    while (true) {
        string sourceCode;
        cout << "Input: ";
        cin >> sourceCode;

        Lexer lexer(sourceCode);
        Parser parser(lexer);

        int result = parser.parse();

        cout << "Result: " << result << endl << endl;
    }

    return 0;
}
