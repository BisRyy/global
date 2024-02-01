// Lexer.h
#include <string>
#include "globals.h"

#ifndef ERROR_H
#define ERROR_H

void handleError(const char* msg, const char* file, int line, bool abort);
void handleError(const char* msg, int line, bool abort);
void handleError(const char* msg, bool abort);
void handleError(const char* msg);

void handleWarning(const char* msg, const char* file, int line);
void handleWarning(const char* msg, int line);
void handleWarning(const char* msg, bool abort);
void handleWarning(const char* msg);

void handleError(const string msg, const string file, int line, bool abort);
void handleError(const string msg, int line, bool abort);
void handleError(const string msg, bool abort);
void handleError(const string msg);

void handleWarning(const string msg, const string file, int line);
void handleWarning(const string msg, int line);
void handleWarning(const string msg, bool abort);
void handleWarning(const string msg);


#endif // ERROR_H
