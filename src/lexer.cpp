#include "lexer.h"

const std::string lexer::r_num = "[0-9.]",
        lexer::r_lb = "\n",
        lexer::r_comment = "$",
        lexer::r_symbol = "[a-zA-Z_0-9]",
        lexer::r_op = "\\+|-|\\*|\\/|=|>|<|>=|<=|&|\\||%|!|\\^|\\.|\\,";

lexer::lexer(fstream _stream) {
    line = 1;
    stream = _stream;
}

bool lexer::matches(const char &c, const std::string &expr) const {
    std::string target;
    std::regex reg_expr(expr);
    target.push_back(c);
    return std::regex_match(target, reg_expr);
}

std::string lexer::scan_regex(const std::string &expr) {
    std::string ret;
    ret.push_back(stream.curr());
    while (matches(stream.next(), expr)) {
        ret.push_back(stream.next());
        stream.move();
    }
    return ret;
}

std::string lexer::scan_str(const char &delim) {
    std::string ret;
    while (stream.next() != 0) {
        char prev = stream.curr();
        stream.move();
        if (stream.curr() == delim)
            return ret;
        else if (prev == '\\' && stream.curr() == 'n') {
            ret.pop_back();
            ret.push_back('\n');
        } else ret.push_back(stream.curr());
    }
    err("unclosed string", line);
    return ret;
}

void lexer::scan_lb() {
    while (matches(stream.next(), r_lb)) {
        ++line;
        stream.move();
    }
}

void lexer::scan_comment() {
    while (stream.next() != 0) {
        stream.move();
        if (matches(stream.curr(), r_lb)) {
            ++line;
            return;
        }
    }
}

std::vector <token> lexer::tokenize() {
    std::vector <token> tokens;
    while (stream.next()) {
        stream.move();
        char curr = stream.curr();
        if (curr == EOF)
            tokens.emplace_back("EOF", line, t_eof);
        else if (curr == ' ')
            continue;
        else if (curr == '"')
            tokens.emplace_back(scan_str(), line, t_str);
        else if (matches(curr, r_num))
            tokens.emplace_back(scan_regex(r_num), line, t_num);
        else if (matches(curr, r_lb)) {
            ++line;
            scan_lb();
            tokens.emplace_back("LB", line, t_lb);
        } else if (curr == r_comment.front())
            scan_comment();
        else if (matches(curr, r_symbol)) {
            std::string val = scan_regex(r_symbol);
            if (token::builtins.find(val) != token::builtins.end())
                tokens.emplace_back(val, line, t_builtin, token::builtins[val].first);
            else
                tokens.emplace_back(val, line, t_symbol);
        } else if (curr == '(' || curr == ')') {
            std::string val;
            val.push_back(curr);
            tokens.emplace_back(val, line, t_builtin, token::builtins[val].first);
        } else if (matches(curr, r_op)) {
            std::string val = scan_regex(r_op);
            if (token::builtins.find(val) != token::builtins.end())
                tokens.emplace_back(val, line, t_builtin, token::builtins[val].first);
            else
                err("unrecognized operator", line);
        } else {
            err("unrecognized symbol", line);
        }
    }
    return tokens;
}

