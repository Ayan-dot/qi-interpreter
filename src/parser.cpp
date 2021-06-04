#include "parser.h"

parser::parser(std::vector<token> &tokens){
    s_t["gvars_found"] = 0;
    s_t["in_fn"] = 0;
    s_t["main_found"] = 0;
    int parse_ind = 0;
    int start = 0;
    std::string identifier;
    while (parse_ind < tokens.size()){
        if ((tokens[parse_ind].val == "num" || tokens[parse_ind].val == "str" || tokens[parse_ind].val == "arr" || tokens[parse_ind].val == "bool") && !s_t["gvars_found"]) {
            start = parse_ind;
            while (tokens[parse_ind].type != linebreak) {
                if (parse_ind == start + 1 && parse_ind < tokens.size())
                    identifier = tokens[parse_ind].val;
                ++parse_ind;
            }
            global_vars[identifier] = ast_node(ast_node::subarray(tokens, start, parse_ind-1));
            parse_ind++;
        }
        else if ((tokens[parse_ind].val == "num" || tokens[parse_ind].val == "str" || tokens[parse_ind].val == "arr" || tokens[parse_ind].val == "bool")) {
            throw_error("Global variable declaration breaks program structure.", tokens[parse_ind].line_number);
            std::exit(1);
        }
        else if (tokens[parse_ind].val == "fn" && !s_t["main_found"]) {
            s_t["gvars_found"] = 1;
            start = parse_ind;
            while (tokens[parse_ind].val != "end") {
                if (parse_ind == start + 1 && parse_ind < tokens.size())
                    identifier = tokens[parse_ind].val;
                    if(identifier == "main")
                        s_t["main_found"] = 1;
                ++parse_ind;
            }
            global_fn_defs[identifier] = ast_node(ast_node::subarray(tokens, start, parse_ind));
            parse_ind++;
        }
        else {
            if(tokens[parse_ind].val == "fn"){
                throw_error("Function declaration cannot occur after main.", tokens[parse_ind].line_number);
                std::exit(1);
            }
            else if(tokens[parse_ind].type == linebreak) {
                parse_ind++;
            }
            else {
                throw_error("Invalid symbol outside of function scopes", tokens[parse_ind].line_number);
                std::exit(1);
            }
        }
    }
    if (!s_t["main_found"]) {
        throw_error("Main function was not found in program;", tokens[parse_ind].line_number);
            std::exit(1);
    }

}