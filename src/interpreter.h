#ifndef QI_INTERPRETER_INTERPRETER_H
#define QI_INTERPRETER_INTERPRETER_H

#include <chrono>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>

#include "executor.h"
#include "memory.h"
#include "token.h"
#include "util.h"

class interpreter {
private:
    std::vector <token> tokens;

public:
    interpreter(std::vector <token> &tokens);

    static void declare_obj(std::vector <token> obj, bool to_global = false);

    bool declare_fn(int start, int end);

    void execute();
};


#endif //QI_INTERPRETER_INTERPRETER_H
