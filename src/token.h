#ifndef QI_TOKEN_H
#define QI_TOKEN_H

#include <string>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

enum token_type {
    null,
    str,
    num,
    linebreak,
    eof,
    symbol,
    builtin,
    group
};

struct token {
    std::string val;
    token_type type;
    int ops, line_number;
    static std::unordered_map<std::string, int> builtins;
    static std::unordered_map<std::string, int> precedence;
    static int highest_pre;
    static std::unordered_set<std::string> control;

    explicit token(std::string _val = "", int _line_number = -1, token_type _type = null, int _ops = 0);
    static void init();
    std::string str() const;
};

#endif //QI_TOKEN_H
