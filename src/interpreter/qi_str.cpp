#include "qi_str.h"

qi_str::qi_str() {}
qi_str::qi_str(std::string _identifier, ast_node _var_tree) {
  identifier = _identifier;
  var_tree = _var_tree;
}