#include "util.h"

void out() {
    std::cout << "[empty info]" << std::endl;
}

void out(std::string message) {
    std::cout << "[info] " << message << std::endl;
}

void err() {
    std::cout << "\033[1;31m" << "[empty error]" << "\033[0m" << std::endl;
    exit(1);
}

void err(std::string message) {
    std::cout << "\033[1;31m" << "[error]" << "\033[0m" << " " << message << std::endl;
    exit(1);
}

void err(std::string message, int line_number) {
    std::cout << "\033[1;31m" << "[error, line: " << line_number << "]" << "\033[0m" << " " << message << std::endl;
    exit(1);
}