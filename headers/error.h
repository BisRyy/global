// Lexer.h
#include <string>
#include "globals.h"

#ifndef ERROR_H
#define ERROR_H

void handleError(const string msg, int line, int column, bool abort);
void handleError(const string msg, int line, int column);
void handleWarning(const string msg, int line, int column, bool abort);
void handleWarning(const string msg, int line, int column);
void handleLog(const string msg, int line, int column, bool abort);
void handleLog(const string msg, int line, int column);
void handlePrint(string msg);
void handlePrint(int msg);


#endif // ERROR_H
