/*
 * ast_node.h contains:
 *   - Declarations for the Abstract Syntax Tree Node
 */

#ifndef QI_INTERPRETER_AST_NODE_H
#define QI_INTERPRETER_AST_NODE_H

#include <iostream>
#include <string>
#include <vector>

#include "token.h"
#include "util.h"

/// ast_node is a node in the Abstract Syntax Tree that recursively
/// creates its children nodes upon initialization, performing
/// basic syntax and grammar validation
class ast_node {
public:
    token val;
    std::vector <ast_node> children;

    explicit ast_node(std::vector <token> tokens = std::vector<token>());

    static std::vector <std::pair<int, int>> gen_blocks(const std::vector <token> &tokens, bool disallow_fn = true);

    static std::vector <token> subarray(const std::vector <token> &tokens, int start, int end);

    bool is_fn(std::vector <token> &tokens);

    void print();
};

#endif //QI_INTERPRETER_AST_NODE_H
