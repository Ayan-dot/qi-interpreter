#ifndef qi_str_H_
#define qi_str_H_

#include "../ast_node.h"
#include "qi_object.h"

class qi_str : public qi_object {
 private:
  std::string identifier;
  ast_node var_tree;

 public:
  qi_str();
  qi_str(std::string _identifier, ast_node _var_tree);
};

#endif