#ifndef QI_PARSER_H
#define QI_PARSER_H

#include <lexer.h>
#include <ast_node.h>

class parser
{
private:
    std::unordered_map<std::string, ast_node> global_vars;
    std::unordered_map<std::string, ast_node> global_fn_defs;
public:
    parser();
    parser(std::vector<Token> &tokens);
}

#endif
