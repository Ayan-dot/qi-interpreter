#ifndef QI_LEXER_H
#define QI_LEXER_H

#include <iostream>
#include <regex>
#include <string>
#include <vector>

#include "error.h"
#include "file_stream.h"
#include "token.h"

class lexer {
private:
    file_stream stream;
    int line_number;
    static const std::string r_num, r_lb, r_comment, r_symbol, r_op;

public:
    explicit lexer(file_stream _stream);
    bool matches(const char& c, const std::string& expr) const;
    std::string scan_regex(const std::string& expr);
    std::string scan_str(const char& delim = '"');
    void scan_lb();
    void scan_comment();
    std::vector<token> tokenize();
};

#endif //QI_LEXER_H
