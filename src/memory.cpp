/*
 * memory.cpp contains:
 *   - Definitions for the memory class
 *   - Global memory scope definition
 *   - Memory stack definition
 */

#include "memory.h"

memory *memory::global = new memory();
std::stack<memory *> memory::stack = std::stack<memory *>();

/// checks if a symbol is defined in memory
/// \param id: the symbol name
/// \return whether a symbol exists in memory
bool memory::has(std::string id) {
    return (memory::global->table.find(id) != memory::global->table.end()) ||
           (!memory::stack.empty() && memory::stack.top()->table.find(id) != memory::stack.top()->table.end());
}

/// check whether a symbol name is valid and can be added to the
/// memory without causing any naming collisions
/// \param id: the symbol name
/// \return whether this symbol name can be added to memory
bool memory::valid(std::string id) {
    return !has(id) && id != "main" &&
           token::builtins.find(id) == token::builtins.end() &&
           token::vars.find(id) == token::vars.end() &&
           token::control.find(id) == token::control.end() &&
           token::methods.find(id) == token::methods.end();
}

/// add a symbol and the respective object to memory
/// \param id: the symbol name
/// \param obj: the object
/// \param to_global: whether this should be to the global memory
void memory::add(std::string id, object *obj, bool to_global) {
    if (to_global)
        memory::global->table[id] = obj;
    else {
        if (memory::stack.empty())
            err("no memory scope on the stack");
        memory::stack.top()->table[id] = obj;
    }
}

/// removes a symbol from the memory
/// \param id: the symbol name
void memory::remove(std::string id) {
    if (memory::stack.top()->table.find(id) == memory::stack.top()->table.end())
        err("tried removing non-existing variable");
    memory::stack.top()->table.erase(id);
}

/// get the object mapped to the symbol name
/// \param id: the symbol name
/// \return the mapped object
object *memory::get(std::string id) {
    if (memory::global->table.find(id) != memory::global->table.end())
        return memory::global->table[id];
    else if (!memory::stack.empty() && memory::stack.top()->table.find(id) != memory::stack.top()->table.end())
        return memory::stack.top()->table[id];
    else {
        err("obj does not exist in memory");
        return (new object());
    }
}

/// pushes a new memory stack
void memory::push() {
    memory::stack.push(new memory());
}

/// pops the last memory stack
void memory::pop() {
    if (memory::stack.empty())
        err("attempted to pop empty memory stack");
    memory *top = memory::stack.top();
    memory::stack.pop();
    delete top;
}

/// empty constructor for memory objects
memory::memory() {}
