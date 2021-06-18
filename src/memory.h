/*
 * memory.h contains:
 *   - Declarations for the memory
 */

#ifndef QI_INTERPRETER_MEMORY_H
#define QI_INTERPRETER_MEMORY_H

#include <string>
#include <stack>
#include <unordered_map>

#include "object.h"
#include "util.h"

/// the memory object is functionally a symbol table lookup with
/// utilities for adding, removing, and checking if certain symbols
/// exist in the symbol table
class memory {
public:
    static memory *global;
    static std::stack<memory *> stack;

    std::unordered_map<std::string, object *> table;

    static bool has(std::string id);

    static bool valid(std::string id);

    static void add(std::string id, object *obj, bool to_global = false);

    static void remove(std::string id);

    static object *get(std::string id);

    static void push();

    static void pop();

    memory();
};

#endif //QI_INTERPRETER_MEMORY_H
