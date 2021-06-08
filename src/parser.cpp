#include "parser.h"

parser::parser(std::vector<token>& tokens) {
  int scope_lvl = 0;
  int parse_ind = 0;
  int start = 0;
  int depth = 0;
  std::string identifier;
  std::string return_type;
  std::vector<std::pair<std::string, std::string>> paramlist;
  bool more_params = true;
  while (parse_ind < tokens.size()) {
    if (token::vars.find(tokens[parse_ind].val) != token::vars.end()) {
      if (scope_lvl > 0)
        throw_error("incorrect program structure: global var scope has passed",
                    tokens[parse_ind].line_number);
      start = parse_ind;
      parse_ind++;
      identifier = tokens[parse_ind].val;
      if (global_vars.find(identifier) != global_vars.end()) {
        throw_error("variable has already been declared",
                    tokens[parse_ind].line_number);
      }
      parse_ind++;
      if (tokens[parse_ind].val != "=" && tokens[parse_ind].type != linebreak) {
        throw_error("invalid variable declaration syntax",
                    tokens[parse_ind].line_number);
      }
      while (tokens[parse_ind].type != linebreak) {
        ++parse_ind;
      }
      if (tokens[parse_ind].val == "num")
        global_vars[identifier] = qi_num(
            identifier,
            ast_node(ast_node::subarray(tokens, start, parse_ind - 1)));
      else if (tokens[parse_ind].val == "str")
        global_vars[identifier] = qi_str(
            identifier,
            ast_node(ast_node::subarray(tokens, start, parse_ind - 1)));
      else if (tokens[parse_ind].val == "bool")
        global_vars[identifier] = qi_bool(
            identifier,
            ast_node(ast_node::subarray(tokens, start, parse_ind - 1)));

      parse_ind++;
    } 
    else if (tokens[parse_ind].val == "fn" && scope_lvl <= 1) {
      paramlist.clear();
      if (tokens.size() - parse_ind < 9)
        throw_error("program ends before function declaration finishes",
                    tokens[parse_ind].line_number);
      scope_lvl = 1;
      identifier = tokens[++parse_ind].val;
      if (identifier == "main") scope_lvl = 2;
      parse_ind++;
      return_type = tokens[parse_ind].val;
      parse_ind++;
      if (tokens[parse_ind].val != "(")
        throw_error("missing open bracket for function params",
                    tokens[parse_ind].line_number);
      ++parse_ind;
      while (tokens[parse_ind].val != ")") {
        if(tokens[parse_ind].val == "void" || tokens[parse_ind].val == ",") {
          parse_ind++;
          continue;
        }
        if(token::vars.find(tokens[parse_ind].val) != token::vars.end() && tokens[parse_ind + 1].val != ")") {
          paramlist.push_back(
            std::make_pair(tokens[parse_ind].val, tokens[parse_ind + 1].val));
          parse_ind+=2;
        }
        else
          break;
      }
      if (tokens[parse_ind].val != ")"){
        throw_error("missing close bracket for function params",
                    tokens[parse_ind].line_number);}
      ++parse_ind;
      if (tokens[parse_ind].val != "start")
        throw_error("missing block sequence for function",
                    tokens[parse_ind].line_number);
      depth = 1;
      ++parse_ind;
      start = parse_ind;
      while (!(depth == 1 && tokens[parse_ind].val == "end")) {
            if (tokens[parse_ind].val == "start") ++depth;
            if (tokens[parse_ind].val == "end") --depth;
        ++parse_ind;
        std::cout << parse_ind << " vs " << tokens.size() << std::endl;
        if(parse_ind == tokens.size())
         throw_error("unclosed block", tokens[parse_ind].line_number);
      }
      if (tokens[parse_ind].val != "end") {
        throw_error("unclosed block", tokens[parse_ind].line_number);
      }
      global_fn_defs[identifier] =
           qi_fn(return_type, identifier, paramlist,
                    new ast_node(ast_node::subarray(tokens, start+1, parse_ind-2)));
      parse_ind++;
    } 
    else if (tokens[parse_ind].val == "fn") {
      if (scope_lvl > 1)
        throw_error(
            "incorrect program structure: fn main has already been declared",
            tokens[parse_ind].line_number);
    } 
    else if (tokens[parse_ind].type == linebreak || tokens[parse_ind].type == eof) {
      parse_ind++;
    } 
    else {
      throw_error("Invalid symbol outside of function scopes",
                  tokens[parse_ind].line_number);
      std::exit(1);
    }
  }
  if (scope_lvl == 1) {
    throw_error("main function was not found in program;",
                tokens[parse_ind].line_number);
    std::exit(1);
  }
  for (auto i : global_fn_defs) {
    i.second.print();
  }
}