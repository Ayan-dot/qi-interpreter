#include "qi_num.h"

qi_num::qi_num() {}
qi_num::qi_num(std::string _identifier, ast_node _var_tree) {
  identifier = _identifier;
  var_tree = _var_tree;
}