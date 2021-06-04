#ifndef QI_ERROR_H
#define QI_ERROR_H

#include <iostream>
#include <cstdlib>
#include <string>

void throw_error();
void throw_error(std::string error_message);
void throw_error(std::string error_message, int line_number);

#endif //QI_ERROR_H
