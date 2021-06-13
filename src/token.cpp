#include "token.h"

std::unordered_map <std::string, std::pair<int, int>> token::builtins =
        std::unordered_map < std::string, std::pair<int, int>>
();
std::unordered_set <std::string> token::control = std::unordered_set<std::string>();
std::unordered_set <std::string> token::vars = std::unordered_set<std::string>();
int token::pre_none = 12;

void token::init() {
    token::builtins.insert({"+", {2, 5}});
    token::builtins.insert({"-", {2, 5}});
    token::builtins.insert({"*", {2, 6}});
    token::builtins.insert({"**", {2, 7}});
    token::builtins.insert({"/", {2, 6}});
    token::builtins.insert({"==", {2, 3}});
    token::builtins.insert({"!=", {2, 3}});
    token::builtins.insert({"<", {2, 3}});
    token::builtins.insert({"<=", {2, 3}});
    token::builtins.insert({">", {2, 3}});
    token::builtins.insert({">=", {2, 3}});
    token::builtins.insert({"^", {2, 9}});
    token::builtins.insert({"|", {2, 10}});
    token::builtins.insert({"&", {2, 10}});
    token::builtins.insert({">>", {2, 7}});
    token::builtins.insert({"<<", {2, 7}});
    token::builtins.insert({"%", {2, 6}});
    token::builtins.insert({"=", {2, 1}});
    token::builtins.insert({"-=", {2, 1}});
    token::builtins.insert({"+=", {2, 1}});
    token::builtins.insert({"*=", {2, 1}});
    token::builtins.insert({"**=", {2, 1}});
    token::builtins.insert({"/=", {2, 1}});
    token::builtins.insert({"%=", {2, 1}});
    token::builtins.insert({">>=", {2, 1}});
    token::builtins.insert({"<<=", {2, 1}});
    token::builtins.insert({"&=", {2, 1}});
    token::builtins.insert({"|=", {2, 1}});
    token::builtins.insert({"^=", {1, 2}});
    token::builtins.insert({",", {2, 2}});
    token::builtins.insert({"and", {2, 11}});
    token::builtins.insert({"not", {1, 4}});
    token::builtins.insert({"or", {2, 12}});
    token::builtins.insert({"if", {2, 2 * token::pre_none}});
    token::builtins.insert({"else", {1, 2 * token::pre_none}});
    token::builtins.insert({"start", {0, 2 * token::pre_none}});
    token::builtins.insert({"end", {0, 2 * token::pre_none}});
    token::builtins.insert({"break", {0, 2 * token::pre_none}});
    token::builtins.insert({"continue", {0, 2 * token::pre_none}});
    token::builtins.insert({"while", {2, 2 * token::pre_none}});
    token::builtins.insert({"for", {2, 2 * token::pre_none}});
    token::builtins.insert({"of", {2, -1}});
    token::builtins.insert({"in", {1, 0}});
    token::builtins.insert({"out", {1, 0}});
    token::builtins.insert({"return", {1, 0}});
    token::builtins.insert({"fn", {4, 2 * token::pre_none}});
    token::builtins.insert({"num", {1, 0}});
    token::builtins.insert({"bool", {1, 0}});
    token::builtins.insert({"str", {1, 0}});
    token::builtins.insert({"arr", {1, 0}});
    token::builtins.insert({"map", {1, 0}});
    token::builtins.insert({"set", {1, 0}});
    token::builtins.insert({"queue", {1, 0}});
    token::builtins.insert({"stack", {1, 0}});
    token::builtins.insert({"(", {0, 2 * token::pre_none}});
    token::builtins.insert({")", {0, 2 * token::pre_none}});
    token::builtins.insert({".", {2, 8}});

    token::control.insert("if");
    token::control.insert("else");
    token::control.insert("for");
    token::control.insert("while");

    token::vars.insert("num");
    token::vars.insert("bool");
    token::vars.insert("str");
    token::vars.insert("arr");
    token::vars.insert("map");
    token::vars.insert("set");
    token::vars.insert("queue");
    token::vars.insert("stack");
    token::vars.insert("none");
}

token::token(std::string _val, int _line, t_type _type, int _ops) {
    val = _val;
    line = _line;
    type = _type;
    ops = _ops;
}

std::string token::str() const {
    std::stringstream ret;
    ret << "<token: \"" << val << "\", " << line << ", " << type << ", " << ops << ">";
    return ret.str();
}

token &token::operator=(const token &other) = default;