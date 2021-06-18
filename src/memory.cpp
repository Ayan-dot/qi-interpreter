#include "memory.h"

memory *memory::global = new memory();
std::stack<memory *> memory::stack = std::stack<memory *>();

bool memory::has(std::string id) {
    return (memory::global->table.find(id) != memory::global->table.end()) ||
           (!memory::stack.empty() && memory::stack.top()->table.find(id) != memory::stack.top()->table.end());
}

bool memory::valid(std::string id) {
    return !has(id) && id != "main" &&
           token::builtins.find(id) == token::builtins.end() &&
           token::vars.find(id) == token::vars.end() &&
           token::control.find(id) == token::control.end();
}

void memory::add(std::string id, object *obj, bool to_global) {
    if (to_global)
        memory::global->table[id] = obj;
    else {
        if (memory::stack.empty())
            err("no memory scope on the stack");
        memory::stack.top()->table[id] = obj;
    }
}

void memory::remove(std::string id) {
    if (memory::stack.top()->table.find(id) == memory::stack.top()->table.end())
        err("tried removing non-existing variable");
    memory::stack.top()->table.erase(id);
}

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

void memory::push() {
    memory::stack.push(new memory());
}

void memory::pop() {
    if (memory::stack.empty())
        err("attempted to pop empty memory stack");
    memory *top = memory::stack.top();
    memory::stack.pop();
    delete top;
}

memory::memory() {}