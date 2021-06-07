#include "qi_fn.h"

qi_fn::qi_fn() {}
qi_fn::qi_fn(std::string _return_type, std::string _identifier,
             std::vector<std::pair<std::string, std::string>> _paramlist,
             ast_node _fn_tree) {
  // return_type = _return_type;
  identifier = _identifier;
  // paramlist = _paramlist;
  fn_tree = _fn_tree;
}