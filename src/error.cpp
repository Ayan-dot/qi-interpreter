#include "error.h"

void throw_error() {
    std::cout << "\033[1;31m" << "Error" << "\033[0m\n";
    exit(1);
}

void throw_error(std::string error_message) {
    std::cout << "\033[1;31m" << "Error: " << "\033[0m" << error_message << "\n";
    exit(1);
}

void throw_error(std::string error_message, int line_number) {
    std::cout << "\033[1;31m" << "Error (line " << line_number << "): " << "\033[0m" << error_message << "\n";
    exit(1);
}
