#include "qi_bool.h"

qi_bool::qi_bool() {}
qi_bool::qi_bool(std::string _identifier, ast_node _var_tree) {
  identifier = _identifier;
  var_tree = _var_tree;
}