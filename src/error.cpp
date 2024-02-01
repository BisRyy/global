#include <iostream>
#include "../headers/error.h"

using namespace std;

void handleError(const char* msg, const char* file, int line, bool abort = true) {
    cerr << "\033[1;31m";
    cerr << "Error: " << msg << " in " << file << " at line " << line << endl;
    cerr << "\033[0m";
    if (abort) exit(EXIT_FAILURE);
}

void handleError(const char* msg, int line, bool abort = true) {
    cerr << "\033[1;31m";
    cerr << "Error: " << msg << " at line " << line << endl;
    cerr << "\033[0m";
    if (abort) exit(EXIT_FAILURE);
}

void handleError(const char* msg) {
    cerr << "\033[1;31m";
    cerr << "Error: " << msg << endl;
    cerr << "\033[0m";
    exit(EXIT_FAILURE);
}

void handleError(const char* msg, bool abort) {
    cerr << "\033[1;31m";
    cerr << "Error: " << msg << endl;
    cerr << "\033[0m";
    if (abort) exit(EXIT_FAILURE);
}

void handleWarning(const char* msg, const char* file, int line) {
    cerr << "\033[1;33m";
    cerr << "Warning: " << msg << " in " << file << " at line " << line << endl;
    cerr << "\033[0m";
}

void handleWarning(const char* msg, int line) {
    cerr << "\033[1;33m";
    cerr << "Warning: " << msg << " at line " << line << endl;
    cerr << "\033[0m";
}

void handleWarning(const char* msg) {
    cerr << "\033[1;33m";
    cerr << "Warning: " << msg << endl;
    cerr << "\033[0m";
}

void handleWarning(const char* msg, bool abort) {
    cerr << "\033[1;33m";
    cerr << "Warning: " << msg << endl;
    cerr << "\033[0m";
    if (abort) exit(EXIT_FAILURE);
}

void handleError(const string msg, const string file, int line, bool abort = true) {
    cerr << "\033[1;31m";
    cerr << "Error: " << msg << " in " << file << " at line " << line << endl;
    cerr << "\033[0m";
    if (abort) exit(EXIT_FAILURE);
}

void handleError(const string msg, int line, bool abort = true) {
    cerr << "\033[1;31m";
    cerr << "Error: " << msg << " at line " << line << endl;
    cerr << "\033[0m";
    if (abort) exit(EXIT_FAILURE);
}

void handleError(const string msg) {
    cerr << "\033[1;31m";
    cerr << "Error: " << msg << endl;
    cerr << "\033[0m";
    exit(EXIT_FAILURE);
}

void handleError(const string msg, bool abort) {
    cerr << "\033[1;31m";
    cerr << "Error: " << msg << endl;
    cerr << "\033[0m";
    if (abort) exit(EXIT_FAILURE);
}

void handleWarning(const string msg, const string file, int line) {
    cerr << "\033[1;33m";
    cerr << "Warning: " << msg << " in " << file << " at line " << line << endl;
    cerr << "\033[0m";
}

void handleWarning(const string msg, int line) {
    cerr << "\033[1;33m";
    cerr << "Warning: " << msg << " at line " << line << endl;
    cerr << "\033[0m";
}

void handleWarning(const string msg) {
    cerr << "\033[1;33m";
    cerr << "Warning: " << msg << endl;
    cerr << "\033[0m";
}

void handleWarning(const string msg, bool abort) {
    cerr << "\033[1;33m";
    cerr << "Warning: " << msg << endl;
    cerr << "\033[0m";
    // if (abort) exit(EXIT_FAILURE);
}