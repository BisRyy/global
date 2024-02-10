#include <iostream>
#include <iomanip>
#include "../headers/error.h"

using namespace std;

void handleError(const string msg, int line, int column, bool abort) {
    cerr << "\033[1;31m";
    cerr << line << ":" << column << ": Error: " << msg << endl;
    cerr << "\033[0m";
    if (abort) exit(EXIT_FAILURE);
}

void handleError(const string msg, int line, int column) {
    handleError(msg, line, column, true);
}

void handleWarning(const string msg, int line, int column, bool abort) {
    cerr << "\033[1;33m";
    cerr << line << ":" << column << ": Warning: " << msg << endl;
    cerr << "\033[0m";
    if (abort) exit(EXIT_FAILURE);
}

void handleWarning(const string msg, int line, int column) {
    handleWarning(msg, line, column, false);
}