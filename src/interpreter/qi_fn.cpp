#include "qi_fn.h"
std::unordered_map<std::string, var_type> qi_fn::str_to_type = std::unordered_map<std::string, var_type>();
qi_fn::qi_fn() {}
qi_fn::qi_fn(std::string _return_type, std::string _identifier,
             std::vector<std::pair<std::string, std::string>> _paramlist,
             ast_node *_fn_tree) {
   return_type = str_to_type[_return_type];
   identifier = _identifier;
   for(int i = 0; i < _paramlist.size(); i++) {
     paramlist[_paramlist[i].second] = str_to_type[_paramlist[i].first];
   }
  fn_tree = _fn_tree;
}
void qi_fn::init(){
  str_to_type["str"] = _str;
  str_to_type["num"] = _num;
  str_to_type["bool"] = _bool;
  str_to_type["arr"] = _arr;
  str_to_type["void"] = _null;
}
void qi_fn::print() {
  std::cout << "\nFunction Name: " << identifier << std::endl;
  std::cout << "Return Type: " << return_type << std::endl;
  std::cout << "Parameters: " << std::endl;
  for(auto i : paramlist)
    std::cout << i.first << " with type " << i.second << std::endl;
}