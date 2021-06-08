#include "token.h"

std::unordered_map<std::string, std::pair<int, int>> token::builtins = std::unordered_map<std::string,std::pair<int, int>>();
std::unordered_set<std::string> token::control = std::unordered_set<std::string>();
std::unordered_set<std::string> token::vars = std::unordered_set<std::string>();
int token::highest_pre = 12;

token::token(std::string _val, int _line_number, token_type _type, int _ops) {
    val = std::move(_val);
    line_number = _line_number;
    type = _type;
    ops = _ops;
}

void token::init() {
    // init builtins
    // pair<int, int>: {operations, precedence}
    token::builtins["+"] = std::pair<int, int>(2, 2);
    token::builtins["-"] = std::pair<int, int>(2, 5);
    token::builtins["*"] = std::pair<int, int>(2, 6);
    token::builtins["/"] = std::pair<int, int>(2, 6);
    token::builtins["=="] = std::pair<int, int>(2, 3);
    token::builtins["!="] = std::pair<int, int>(2, 3);
    token::builtins["<"] = std::pair<int, int>(2, 3);
    token::builtins["<="] = std::pair<int, int>(2, 3);
    token::builtins[">"] = std::pair<int, int>(2, 3);
    token::builtins[">="] = std::pair<int, int>(2, 3);
    token::builtins["^"] = std::pair<int, int>(2, 9);
    token::builtins["|"] = std::pair<int, int>(2, 10);
    token::builtins[">>"] = std::pair<int, int>(2, 7);
    token::builtins["<<"] = std::pair<int, int>(2, 7);
    token::builtins["%"] = std::pair<int, int>(2, 6);
    token::builtins["="] = std::pair<int, int>(2, 1);
    token::builtins["-="] = std::pair<int, int>(2, 1);
    token::builtins["+="] = std::pair<int, int>(2, 1);
    token::builtins["*="] = std::pair<int, int>(2, 1);
    token::builtins["/="] = std::pair<int, int>(2, 1);
    token::builtins["%="] = std::pair<int, int>(2, 1);
    token::builtins[">>="] = std::pair<int, int>(2, 1);
    token::builtins["<<="] = std::pair<int, int>(2, 1);
    token::builtins["&="] = std::pair<int, int>(2, 1);
    token::builtins["|="] = std::pair<int, int>(2, 1);
    token::builtins["^="] = std::pair<int, int>(1, 2);
    token::builtins[","] = std::pair<int, int>(2, 2);
    token::builtins["and"] = std::pair<int, int>(2, 11);
    token::builtins["not"] = std::pair<int, int>(1, 4);
    token::builtins["or"] = std::pair<int, int>(2, 12);
    token::builtins["if"] = std::pair<int, int>(2, 2 * token::highest_pre);
    token::builtins["else"] = std::pair<int, int>(1, 2 * token::highest_pre);
    token::builtins["start"] = std::pair<int, int>(0, 2 * token::highest_pre);
    token::builtins["end"] = std::pair<int, int>(0, 2 * token::highest_pre);
    token::builtins["break"] = std::pair<int, int>(0, 2 * token::highest_pre);
    token::builtins["continue"] = std::pair<int, int>(0, 2 * token::highest_pre);
    token::builtins["while"] = std::pair<int, int>(2, 2 * token::highest_pre);
    token::builtins["for"] = std::pair<int, int>(2, 2 * token::highest_pre);
    token::builtins["of"] = std::pair<int, int>(2, -1);
    token::builtins["in"] = std::pair<int, int>(2, 2 * token::highest_pre);
    token::builtins["out"] = std::pair<int, int>(2, 2 * token::highest_pre);
    token::builtins["num"] = std::pair<int, int>(1, 0);
    token::builtins["bool"] = std::pair<int, int>(1, 0);
    token::builtins["str"] = std::pair<int, int>(1, 0);
    token::builtins["arr"] = std::pair<int, int>(1, 0);
    token::builtins["fn"] = std::pair<int, int>(4, 2 * token::highest_pre);
    token::builtins["("] = std::pair<int, int>(0, 2 * token::highest_pre);
    token::builtins[")"] = std::pair<int, int>(0, 2 * token::highest_pre);
    token::builtins["."] = std::pair<int, int>(2, 2);

    // init the control structure keywords
    token::control.insert("if");
    token::control.insert("else");
    token::control.insert("for");
    token::control.insert("while");

    token::vars.insert("num");
    token::vars.insert("str");
    token::vars.insert("arr");
    token::vars.insert("bool");
}

std::string token::str() const {
    std::stringstream ret;
    ret << "<token: \"" << val << "\", " << line_number << ", " << type << ", " << ops << ">";
    return ret.str();
}
