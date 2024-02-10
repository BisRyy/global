// Lexer.h
#include <string>
#include "globals.h"

#ifndef ERROR_H
#define ERROR_H

void handleError(const string msg, int line, int column, bool abort);
void handleError(const string msg, int line, int column);
void handleWarning(const string msg, int line, int column, bool abort);
void handleWarning(const string msg, int line, int column);


#endif // ERROR_H
