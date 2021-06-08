#ifndef QI_FN_H_
#define QI_FN_H_

#include "../ast_node.h"
#include "qi_object.h"

enum var_type {
  _str,
  _num,
  _bool,
  _arr,
  _null
};

class qi_fn : public qi_object {
 private:
  var_type return_type;  // add static func to find ret type from string
  std::string identifier;
  std::unordered_map<std::string, var_type> paramlist;
  ast_node * fn_tree;
  static std::unordered_map<std::string, var_type> str_to_type;

 public:
  qi_fn();
  qi_fn(std::string _return_type, std::string identifier,
        std::vector<std::pair<std::string, std::string>> _paramlist,
        ast_node * _fn_tree);
  void print();
  static void init();
};

#endif