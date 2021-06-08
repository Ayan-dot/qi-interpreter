#ifndef QI_PARSER_H
#define QI_PARSER_H

#include "lexer.h"
#include "ast_node.h"
#include "error.h"
#include <string>
#include <vector>
#include "interpreter/qi_num.h"
#include "interpreter/qi_str.h"
#include "interpreter/qi_bool.h"
#include "interpreter/qi_fn.h"

class parser {
 private:
  std::unordered_map<std::string, qi_object> global_vars;
  std::unordered_map<std::string, qi_fn> global_fn_defs;

 public:
  parser();
  parser(std::vector<token> &tokens);
};

#endif
