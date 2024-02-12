#include <stdio.h>
#include <iostream>
#include <fstream>
#include "headers/globals.h"
#include "headers/lexer.h"
#include "headers/parser.h"
#include <string.h>
#include <vector>

using namespace std;

void showHelp(char* argv[]){
    cout << "Usage: " << argv[0] << " <filename> [-e] [-w] [-log] [-a] [-l] [-h]" << endl;
    cout << "Options:" << endl;
    cout << "  -l, --line:    Compile Line by line" << endl;
    cout << "  -e, --error:   Show errors" << endl;
    cout << "  -w, --warning: Show warnings" << endl;
    cout << "  -log:          Show logs" << endl;
    cout << "  -a, -all:      Show all" << endl;
    cout << "  -h, --help:    Show help" << endl;
}

vector<bool> parseOptions(int argc, char* argv[]){
    vector<bool> options = {false, false, false, false, false, false};
    for (int i = 2; i < argc; i++){
        if (strcmp(argv[i], "-l") == 0 || strcmp(argv[i], "--line") == 0){
            options[0] = true;
        } else if (strcmp(argv[i], "-e") == 0 || strcmp(argv[i], "--error") == 0){
            options[1] = true;
        } else if (strcmp(argv[i], "-w") == 0 || strcmp(argv[i], "--warning") == 0){
            options[2] = true;
        } else if (strcmp(argv[i], "-log") == 0){
            options[3] = true;
        } else if (strcmp(argv[i], "-a") == 0 || strcmp(argv[i], "--all") == 0){
            options[4] = true;
        } else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0){
            options[5] = true;
        } else {
            cerr << "Error: Unknown option '" << argv[i] << "'" << endl;
            showHelp(argv);
            exit(1);
        }
    }
    return options;
}

// main function
int main( int argc, char* argv[] ) { // take file name as parameter
    string line;
    bool lineByLine = false;
    bool error = false;
    bool warning = false;
    bool log = false;

    vector<bool> options = parseOptions(argc, argv);
    lineByLine = options[0];
    error = options[1] || options[4];
    warning = options[2] || options[4];
    log = options[3] || options[4];
    if (options[5]){
        showHelp(argv);
        return 0;
    }

    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <filename> [-e] [-w] [-log] [-a] [-l] [-h]" << endl;
        return 1;
    }

    ifstream file(argv[1]);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file '" << argv[1] << "'" << endl;
        return 1;
    }else{
        string fileExtension, fileName;
        size_t pos = string(argv[1]).find_last_of(".");
        if (pos != string::npos){
            fileExtension = string(argv[1]).substr(pos + 1);
            fileName = string(argv[1]).substr(0, pos);
        }else{
            fileExtension = "";
            fileName = string(argv[1]);
        }

        if (fileExtension == "c" || fileExtension == "cpp" || fileExtension == "java" || fileExtension == "rs" || fileExtension == "php"){
            lineByLine = true;
        }
    }

    if (lineByLine) {
        while (getline(file, line)) {
            Lexer lexer(line);
            Parser parser(lexer, error, warning, log);
            int result = parser.parse();
        }
        return 0;
    }

    string source((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    Lexer lexer(source);
    Parser parser(lexer, error, warning, log);
    int result = parser.parse();

    return 0;
}
