#ifndef qi_bool_H_
#define qi_bool_H_

#include "../ast_node.h"
#include "qi_object.h"

class qi_bool : public qi_object {
 private:
  std::string identifier;
  ast_node var_tree;

 public:
  qi_bool();
  qi_bool(std::string _identifier, ast_node _var_tree);
};

#endif