#include "ast_node.h"

ast_node::ast_node(std::vector<token> tokens) {
    std::vector<std::pair<int, int>> blocks = ast_node::gen_blocks(tokens);
    if (blocks.empty())
        throw_error("parsing error");
    else if (blocks.size() >= 2) {
        val = token("GROUP", tokens[0].line_number, group, (int) blocks.size());
        for (const std::pair<int, int> &block : blocks)
            children.emplace_back(ast_node::subarray(tokens, block.first, block.second));
    }
    else {
        tokens = subarray(tokens, blocks[0].first, blocks[0].second);
        if (tokens.back().val == "end") {
            val = tokens[0];
            int start;
            for (start = 2; start < tokens.size() - 1; ++start)
                if (tokens[start].val == "start")
                    break;
            children.emplace_back(ast_node::subarray(tokens, 1, start - 1));
            if (tokens.size() - start < 4)
                throw_error("empty block", tokens[start].line_number);
            children.emplace_back(ast_node::subarray(tokens, start + 2, (int) tokens.size() - 2));
        } else if (tokens.size() == 1)
            val = tokens[0];
        else {
            int pre = token::highest_pre + 1, lowest_pre = -1;
            for (int i = 0; i < tokens.size(); ++i)
                if (tokens[i].type == builtin && token::precedence[tokens[i].val] < pre)
                    pre = token::precedence[tokens[i].val], lowest_pre = i;
            if (lowest_pre == -1)
                throw_error("unrecognized symbol in expression", tokens[0].line_number);
            val = tokens[lowest_pre];
            if (val.ops == 1) {
                if (lowest_pre != 0)
                    throw_error("unary operator in incorrect position", tokens[0].line_number);
                children.emplace_back(ast_node::subarray(tokens, 1, (int) tokens.size() - 1));
            } else if (val.ops == 2) {
                if (lowest_pre == 0 || lowest_pre == tokens.size() - 1)
                    throw_error("binary operator in incorrect position", tokens[0].line_number);
                children.emplace_back(ast_node::subarray(tokens, 0, lowest_pre - 1));
                children.emplace_back(ast_node::subarray(tokens, lowest_pre + 1, (int) tokens.size() - 1));
            }
        }
    }
}

std::vector<std::pair<int, int>> ast_node::gen_blocks(const std::vector<token> &tokens) {
    std::vector<std::pair<int, int>> blocks;
    int count = (int) tokens.size(), curr = 0, start, depth;
    while (curr < count) {
        if (curr - 1 >= 0 && tokens[curr - 1].type != linebreak)
            throw_error("invalid formatting", tokens[curr - 1].line_number);
        start = curr;
        while (curr < count &&
               !(tokens[curr].type == eof || tokens[curr].type == linebreak || tokens[curr].val == "start"))
            ++curr;
        if (curr == count || tokens[curr].type == eof || tokens[curr].type == linebreak) {
            blocks.emplace_back(start, curr - 1);
            ++curr;
            continue;
        }
        depth = 1, ++curr;
        while (curr < count && tokens[curr].type != eof && !(depth == 1 && tokens[curr].val == "end")) {
            if (tokens[curr].val == "start") ++depth;
            if (tokens[curr].val == "end") --depth;
            ++curr;
        }
        if (curr == count || tokens[curr].type == eof)
            throw_error("unclosed block", tokens[curr - 1].line_number);
        blocks.emplace_back(start, curr);
        curr += 2;
    }
    if (blocks.back().first > blocks.back().second)
        blocks.pop_back();
    return blocks;
}

std::vector<token> ast_node::subarray(const std::vector<token> &tokens, int start, int end) {
    return std::vector<token>(tokens.begin() + start, tokens.begin() + end + 1);
}
