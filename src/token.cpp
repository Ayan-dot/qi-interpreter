#include "token.h"

std::unordered_map<std::string, int> token::builtins = std::unordered_map<std::string, int>();
std::unordered_map<std::string, int> token::precedence = std::unordered_map<std::string, int>();
std::unordered_set<std::string> token::control = std::unordered_set<std::string>();
int token::highest_pre = 12;

token::token(std::string _val, int _line_number, token_type _type, int _ops) {
    val = std::move(_val);
    line_number = _line_number;
    type = _type;
    ops = _ops;
}

void token::init() {
    // init builtins
    token::builtins["+"] = 2;
    token::builtins["++"] = 1;
    token::builtins["--"] = 1;
    token::builtins["-"] = 2;
    token::builtins["*"] = 2;
    token::builtins["/"] = 2;
    token::builtins["=="] = 2;
    token::builtins["!="] = 2;
    token::builtins["<"] = 2;
    token::builtins["<="] = 2;
    token::builtins[">"] = 2;
    token::builtins[">="] = 2;
    token::builtins["^"] = 2;
    token::builtins["|"] = 2;
    token::builtins[">>"] = 2;
    token::builtins["<<"] = 2;
    token::builtins["%"] = 2;
    token::builtins["="] = 2;
    token::builtins["-="] = 2;
    token::builtins["+="] = 2;
    token::builtins["*="] = 2;
    token::builtins["/="] = 2;
    token::builtins["%="] = 2;
    token::builtins[">>="] = 2;
    token::builtins["<<="] = 2;
    token::builtins["&="] = 2;
    token::builtins["|="] = 2;
    token::builtins["^="] = 2;
    token::builtins[","] = 2;
    token::builtins["and"] = 2;
    token::builtins["not"] = 1;
    token::builtins["or"] = 2;
    token::builtins["if"] = 2;
    token::builtins["else"] = 2;
    token::builtins["start"] = 0;
    token::builtins["end"] = 0;
    token::builtins["break"] = 0;
    token::builtins["continue"] = 0;
    token::builtins["while"] = 2;
    token::builtins["for"] = 2;
    token::builtins["of"] = 2;
    token::builtins["in"] = 2;
    token::builtins["out"] = 2;
    token::builtins["num"] = 1;
    token::builtins["bool"] = 1;
    token::builtins["str"] = 1;
    token::builtins["arr"] = 1;
    token::builtins["fn"] = 4;
    token::builtins["("] = 0;
    token::builtins[")"] = 0;

    // set precedence in order [lower is higher]
    token::precedence["in"] = -1;
    token::precedence["num"] = 0;
    token::precedence["bool"] = 0;
    token::precedence["str"] = 0;
    token::precedence["arr"] = 0;
    token::precedence["="] = 1;
    token::precedence["-="] = 1;
    token::precedence["+="] = 1;
    token::precedence["*="] = 1;
    token::precedence["/="] = 1;
    token::precedence["%="] = 1;
    token::precedence[">>="] = 1;
    token::precedence["<<="] = 1;
    token::precedence["&="] = 1;
    token::precedence["|="] = 1;
    token::precedence["^="] = 1;
    token::precedence["."] = 2;
    token::precedence[","] = 2;
    token::precedence["<"] = 3;
    token::precedence[">"] = 3;
    token::precedence["<="] = 3;
    token::precedence[">="] = 3;
    token::precedence["=="] = 3;
    token::precedence["!="] = 3;
    token::precedence["not"] = 4;
    token::precedence["+"] = 5;
    token::precedence["-"] = 5;
    token::precedence["*"] = 6;
    token::precedence["/"] = 6;
    token::precedence["%"] = 6;
    token::precedence["<<"] = 7;
    token::precedence[">>"] = 7;
    token::precedence["&"] = 8;
    token::precedence["^"] = 9;
    token::precedence["|"] = 10;
    token::precedence["and"] = 11;
    token::precedence["or"] = 12;

    // init the control structure keywords
    token::control.insert("if");
    token::control.insert("else");
    token::control.insert("for");
    token::control.insert("while");
}

std::string token::str() const {
    std::stringstream ret;
    ret << "<token: \"" << val << "\", " << line_number << ", " << type << ", " << ops << ">";
    return ret.str();
}
