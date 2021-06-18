/*
 * ast_node.cpp contains:
 *   - Definitions for the Abstract Syntax Tree Node
 *   - Utility static methods, such as vector<token> subarray
 */

#include "ast_node.h"

/// checks if a sequence of tokens is a function call
/// \param tokens: a sequence of tokens
/// \return
///   - true: if the tokens form a function call
///   - false: otherwise
bool ast_node::is_fn(std::vector <token> &tokens) {
    // 1) the function call must be formatted as:
    //    [symbol] [left bracket] [parameters?] [right bracket]
    bool valid = tokens.size() >= 3 && tokens[0].type == t_symbol && tokens[1].val == "(" &&
                 tokens.back().val == ")";
    // 2) to avoid cases like `func1() func2()` from being split as
    //    `func1` with parameter tokens `) func2(`, we validate the
    //    brackets to ensure that the inside of the function call is
    //    a valid parameter call
    if (valid) {
        int i = 2, depth = 0;
        while (i < tokens.size() && !(depth == 0 && tokens[i].val == ")")) {
            if (tokens[i].val == "(") ++depth;
            if (tokens[i].val == ")") --depth;
            ++i;
        }
        valid = (i == (tokens.size() - 1));
    }
    return valid;
}

/// constructs an `ast_node` from a sequence of tokens and
/// recursively constructs its children
/// \param tokens: the sequence of tokens
ast_node::ast_node(std::vector <token> tokens) {
    // find blocks
    std::vector <std::pair<int, int>> blocks = ast_node::gen_blocks(tokens);
    if (blocks.empty())
        err("parsing error");
        // if there are multiple blocks, this is a group -> evaluate each
        // child block as a child
    else if (blocks.size() >= 2) {
        val = token("GROUP", tokens[0].line, t_group, (int) blocks.size());
        for (const std::pair<int, int> &block : blocks)
            children.emplace_back(ast_node::subarray(tokens, block.first, block.second));
    } else {
        tokens = subarray(tokens, blocks[0].first, blocks[0].second);
        // case 1) this is a start-end block
        if (tokens.back().val == "end") {
            // `else` is the only start-end block without a condition
            if (tokens.front().val == "else") {
                val = token(tokens[0].val, tokens[0].line, tokens[0].type, tokens[0].ops);
                int start = 1;
                for (; start < tokens.size(); ++start)
                    if (tokens[start].val == "start")
                        break;
                children.emplace_back(ast_node::subarray(tokens, start + 2, (int) tokens.size() - 2));
            } else {
                // otherwise, blocks are structured to have two children:
                // 1) condition
                // 2) child group
                val = token(tokens[0].val, tokens[0].line, tokens[0].type, tokens[0].ops);
                int start = 2;
                for (; start < tokens.size() - 1; ++start)
                    if (tokens[start].val == "start")
                        break;
                children.emplace_back(ast_node::subarray(tokens, 1, start - 1));
                if (tokens.size() - start < 4)
                    err("empty block", tokens[start].line);
                children.emplace_back(ast_node::subarray(tokens, start + 2, (int) tokens.size() - 2));
            }
        } else if (tokens.size() == 1) {
            // single token blocks are leaves in the trees
            val = token(tokens[0].val, tokens[0].line, tokens[0].type, tokens[0].ops);
        } else if (is_fn(tokens)) {
            // if a this is a function call, the node value is the
            // name of the function and the parameters are structured
            // as the children
            val = token(tokens[0].val, tokens[0].line, tokens[0].type, tokens[0].ops);
            int i = 2, depth = 0;
            std::vector <token> curr;
            // split by the `,` operator
            while (i < tokens.size() - 1) {
                if (depth == 0 && tokens[i].val == ",") {
                    if (!curr.empty())
                        children.emplace_back(curr);
                    curr.clear();
                } else {
                    if (tokens[i].val == "(") ++depth;
                    if (tokens[i].val == ")") --depth;
                    curr.push_back(tokens[i]);
                }
                ++i;
            }
            if (!curr.empty())
                children.emplace_back(curr);
        } else {
            // extract children from brackets (brackets can be
            // ignored when the current node is enclosed in brackets
            bool extracted = true;
            while (extracted && tokens.front().val == "(" && tokens.back().val == ")") {
                extracted = false;
                int count = 0;
                bool valid = true;
                for (int i = 1; i < tokens.size() - 1; ++i) {
                    std::string s = tokens[i].val;
                    if (s != "(" && s != ")")
                        continue;
                    else if (s == "(")
                        ++count;
                    else if (count == 0) {
                        valid = false;
                        break;
                    } else
                        --count;
                }
                if (valid) {
                    tokens.erase(tokens.begin());
                    tokens.pop_back();
                    extracted = true;
                }
            }

            // find the highest precedence operator in the expression
            int pre = token::pre_none + 1, lowest_pre = -1, i = 0, depth;
            while (i < tokens.size()) {
                if (tokens[i].val == "(") {
                    depth = 0;
                    while (i < tokens.size() && !(depth == 1 && tokens[i].val == ")")) {
                        if (tokens[i].val == "(") ++depth;
                        if (tokens[i].val == ")") --depth;
                        ++i;
                    }
                    if (i == tokens.size())
                        err("unclosed bracket: " + tokens[i - 1].val, tokens[i - 1].line);
                }
                if (tokens[i].val == ")" && depth <= 0)
                    err("unopened bracket", tokens[i].line);
                if (tokens[i].type == t_num && tokens[i].val == ".") {
                    tokens[i].type = t_builtin;
                    tokens[i].ops = token::builtins[tokens[i].val].second;
                }
                if (tokens[i].type == t_builtin && token::builtins[tokens[i].val].second <= pre)
                    pre = token::builtins[tokens[i].val].second, lowest_pre = i;

                ++i;
            }
            if (lowest_pre == -1) {
                if (tokens.size() == 1)
                    lowest_pre = 0;
                else
                    err("unrecognized symbol in expression", tokens[0].line);
            }

            // set the val to the operator and recurse the operands
            val = token(tokens[lowest_pre].val, tokens[lowest_pre].line, tokens[lowest_pre].type,
                        tokens[lowest_pre].ops);
            if (val.ops == 1 || (val.val == "-" && (lowest_pre == 0 || lowest_pre == tokens.size() - 1))) {
                if (lowest_pre != 0)
                    err("unary operator in incorrect position", tokens[0].line);
                if (val.val == "-") {
                    std::vector <token> tmp;
                    tmp.emplace_back("0", val.line, t_num, 0);
                    children.emplace_back(tmp);
                }
                children.emplace_back(ast_node::subarray(tokens, 1, (int) tokens.size() - 1));
            } else if (val.ops == 2 || val.val == ".") {
                if (val.val == ".") {
                    val.type = t_builtin;
                    val.ops = 2;
                }
                if (lowest_pre == 0 || lowest_pre == tokens.size() - 1)
                    err("binary operator in incorrect position", tokens[0].line);
                children.emplace_back(ast_node::subarray(tokens, 0, lowest_pre - 1));
                children.emplace_back(ast_node::subarray(tokens, lowest_pre + 1, (int) tokens.size() - 1));
            }
        }
    }
}

/// takes in a sequence of tokens and divides them into blocks, which
/// are defined as any lines starting with start and ending with end
/// or single lines at 0 depth
/// \param tokens: the sequence of tokens
/// \param disallow_fn: defines if error is thrown if `fn` exists
/// \return a list of start and end indices of the blocks
std::vector <std::pair<int, int>> ast_node::gen_blocks(const std::vector <token> &tokens, bool disallow_fn) {
    std::vector <std::pair<int, int>> blocks;
    int count = (int) tokens.size(), curr = 0, start, depth;
    while (curr < count) {
        // should never be reached as blocks are consumed entirely
        // each time the while loop is run
        if (curr - 1 >= 0 && tokens[curr - 1].type != t_lb)
            err("invalid formatting", tokens[curr - 1].line);
        // either start of line or start of block
        start = curr;
        while (curr < count &&
               !(tokens[curr].type == t_eof || tokens[curr].type == t_lb || tokens[curr].val == "start"))
            ++curr;
        if (curr == count || tokens[curr].type == t_eof || tokens[curr].type == t_lb) {
            blocks.emplace_back(start, curr - 1);
            ++curr;
            continue;
        }
        depth = 1, ++curr;
        // get end of block
        while (curr < count && tokens[curr].type != t_eof && !(depth == 1 && tokens[curr].val == "end")) {
            if (tokens[curr].val == "start") ++depth;
            if (tokens[curr].val == "end") --depth;
            ++curr;
        }
        if (curr == count || tokens[curr].type == t_eof) {
            for (token t : tokens)
                std::cout << t.str() << std::endl;
            err("unclosed block", tokens[curr - 1].line);
        }
        // validate function definition
        if (disallow_fn && tokens[start].val == "fn")
            err("cannot have nested functions", tokens[start].line);
        blocks.emplace_back(start, curr);
        curr += 2;
    }
    if (blocks.back().first > blocks.back().second)
        blocks.pop_back();
    return blocks;
}

/// returns a subarray from the base array within the range start to
/// inclusive
/// \param tokens: the base tokens array
/// \param start: the start index
/// \param end: the end index
/// \return tokens[start:end + 1]
std::vector <token> ast_node::subarray(const std::vector <token> &tokens, int start, int end) {
    return std::vector<token>(tokens.begin() + start, tokens.begin() + end + 1);
}

/// prints the ast_node
void ast_node::print() {
    std::cout << val.val << "\n";
    for (ast_node u : children)
        u.print();
}
