#ifndef QI_INTERPRETER_UTIL_H
#define QI_INTERPRETER_UTIL_H

#include <iostream>
#include <cstdlib>
#include <string>


void out();

void out(std::string message);

void err();

void err(std::string message);

void err(std::string message, int line_number);


#endif //QI_INTERPRETER_UTIL_H