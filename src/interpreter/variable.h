#ifndef QI_VARIABLE_H
#define QI_VARIABLE_H
#include "qi_object.h"

enum var_type
{
  var_num,
  var_str,
  var_bool,
  var_null

};

class variable : public qi_object
{
private:
public:
  variable();
  variable(var_type type);
};

#endif