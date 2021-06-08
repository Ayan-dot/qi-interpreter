#ifndef QI_AST_NODE_H
#define QI_AST_NODE_H

#include <iostream>
#include <string>
#include <vector>

#include "error.h"
#include "token.h"

struct ast_node {
    token val;
    std::vector<ast_node> children;

    explicit ast_node(std::vector<token> tokens = std::vector<token>());
    static std::vector<std::pair<int, int>> gen_blocks(const std::vector<token>& tokens);
    static std::vector<token> subarray(const std::vector<token>& tokens, int start, int end);
    void print();
};

#endif //QI_AST_NODE_H
