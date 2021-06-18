#ifndef QI_INTERPRETER_TOKEN_H
#define QI_INTERPRETER_TOKEN_H

#include <string>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>


enum t_type {
    t_none,
    t_group,
    t_builtin,
    t_symbol,
    t_num,
    t_str,
    t_lb,
    t_eof
};


class token {
public:
    static std::unordered_map <std::string, std::pair<int, int>> builtins;
    static std::unordered_set <std::string> control, vars, methods;
    static int pre_none;

    std::string val;
    t_type type;
    int ops, line;

    static void init();

    explicit token(std::string _val = "", int _line = -1, t_type _type = t_none, int _ops = 0);

    std::string str() const;

    token &operator=(const token &other);
};


#endif //QI_INTERPRETER_TOKEN_H