#include "lexer.h"

const std::string lexer::r_num = "[0-9.]",
                  lexer::r_lb = "\n",
                  lexer::r_comment = "$",
                  lexer::r_symbol = "[a-zA-Z_0-9]",
                  lexer::r_op = "\\+|-|\\*|\\/|=|>|<|>=|<=|&|\\||%|!|\\^|\\(|\\)|\\.|\\,";

lexer::lexer(file_stream _stream) {
    line_number = 1;
    stream = _stream;
}

bool lexer::matches(const char& c, const std::string& expr) const {
    std::string target;
    std::regex reg_expr(expr);
    target.push_back(c);
    return std::regex_match(target, reg_expr);
}

std::string lexer::scan_regex(const std::string& expr) {
    std::string ret;
    ret.push_back(stream.curr());
    while (matches(stream.next(), expr)) {
        ret.push_back(stream.next());
        stream.move();
    }
    return ret;
}

std::string lexer::scan_str(const char& delim) {
    std::string ret;
    while (stream.next() != '\0') {
        stream.move();
        if (stream.curr() == delim)
            return ret;
        ret.push_back(stream.curr());
    }
    throw_error("unclosed string", line_number);
    return ret;
}

void lexer::scan_lb() {
    while (matches(stream.next(), r_lb)) {
        ++line_number;
        stream.move();
    }
}

void lexer::scan_comment() {
    while (stream.next() != '\0') {
        stream.move();
        if (matches(stream.curr(), r_lb))
            return;
    }
}

std::vector<token> lexer::tokenize() {
    std::vector<token> tokens;
    while (stream.next() != '\0') {
        stream.move();
        char curr = stream.curr();
        if (curr == EOF)
            tokens.emplace_back("EOF", line_number, eof);
        else if (curr == ' ')
            continue;
        else if (curr == '"')
            tokens.emplace_back(scan_str(), line_number, str);
        else if (matches(curr, r_num))
            tokens.emplace_back(scan_regex(r_num), line_number, num);
        else if (matches(curr, r_lb)) {
            ++line_number; scan_lb();
            tokens.emplace_back("LB", line_number, linebreak);
        }
        else if (matches(curr, r_comment))
            scan_comment();
        else if (matches(curr, r_symbol)) {
            std::string val = scan_regex(r_symbol);
            if (token::builtins.find(val) != token::builtins.end())
                tokens.emplace_back(val, line_number, builtin, token::builtins[val]);
            else
                tokens.emplace_back(val, line_number, symbol);
        }
        else if (matches(curr, r_op)) {
            std::string val = scan_regex(r_op);
            if (token::builtins.find(val) != token::builtins.end())
                tokens.emplace_back(val, line_number, builtin, token::builtins[val]);
            else
                throw_error("unrecognized operator", line_number);
        }
        else
            throw_error("unrecognized symbol", line_number);
    }
    return tokens;
}
