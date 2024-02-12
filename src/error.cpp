#include <iostream>
#include <iomanip>
#include "../headers/error.h"

using namespace std;

void handleError(const string msg, int line, int column, bool show) {
    if (show){
        cerr << "\033[1;31m";
        cerr << line << ":" << column << ": Error: " << msg << endl;
        cerr << "\033[0m";
    }
}

void handleError(const string msg, int line, int column) {
    handleError(msg, line, column, false);
}

void handleWarning(const string msg, int line, int column, bool show) {
    if (show){
        cerr << "\033[1;33m";
        cerr << line << ":" << column << ": Warning: " << msg << endl;
        cerr << "\033[0m";
    }
}

void handleWarning(const string msg, int line, int column) {
    handleWarning(msg, line, column, false);
}

void handleLog(const string msg, int line, int column, bool show) {
    if (show){
        clog << "\033[34m";
        clog << line << ":" << column << ": Log: " << msg << endl;
        clog << "\033[0m";
    }
}

void handleLog(const string msg, int line, int column) {
    handleLog(msg, line, column, false);
}

void handlePrint(string msg){
    cout << "\033[32m"; 
    cout << msg << endl;
    cout << "\033[0m"; 
}

void handlePrint(int msg){
    cout << "\033[32m"; 
    cout << msg << endl;
    cout << "\033[0m"; 
}