#ifndef QI_NUM_H_
#define QI_NUM_H_

#include "../ast_node.h"
#include "qi_object.h"

class qi_num : public qi_object {
 private:
  std::string identifier;
  ast_node var_tree;

 public:
  qi_num();
  qi_num(std::string _identifier, ast_node _var_tree);
};

#endif