#ifndef QI_PARSER_H
#define QI_PARSER_H

#include "lexer.h"
#include "ast_node.h"
#include "error.h"

class parser
{
private:
    std::unordered_map<std::string, ast_node> global_vars;
    std::unordered_map<std::string, ast_node> global_fn_defs;
    token curr;
    std::unordered_map<std::string, bool> s_t;
public:
    parser();
    parser(std::vector<token> &tokens);
};

#endif
