#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include "../headers/lexer.h"

using namespace std;
void printToken(Token currentToken);

int main( int argc, char *argv[] ) {
    // read file
    ifstream file(argv[1]);
    string source((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());

    // print the source code
    // cout << source << endl;
    cout << setw(12) << left << "TOKEN TYPE" << setw(15) << left << "VALUE" << " LINE   "<< " COLUMN    " << endl;
    cout << "--------------------------------------" << endl;

    // tokenize the source code
    Lexer lexer(source);
    Token currentToken = lexer.getNextToken();
    while (currentToken.type != TokenType::END_OF_FILE) {
        printToken(currentToken);
        currentToken = lexer.getNextToken();
    }
}