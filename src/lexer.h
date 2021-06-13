#ifndef QI_INTERPRETER_LEXER_H
#define QI_INTERPRETER_LEXER_H

#include <iostream>
#include <regex>
#include <string>
#include <vector>

#include "fstream.h"
#include "token.h"
#include "util.h"


class lexer {
private:
    fstream stream;
    int line;
    static const std::string r_num, r_lb, r_comment, r_symbol, r_op;

public:
    explicit lexer(fstream _stream);

    bool matches(const char &c, const std::string &expr) const;

    std::string scan_regex(const std::string &expr);

    std::string scan_str(const char &delim = '"');

    void scan_lb();

    void scan_comment();

    std::vector <token> tokenize();
};


#endif //QI_INTERPRETER_LEXER_H