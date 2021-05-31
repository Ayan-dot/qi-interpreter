#ifndef TOKEN_H_INCLUDED
#define TOKEN_H_INCLUDED

#include <string>

enum Type {
  Operator,
  Punctuation,
  Number,
  String,
  Control,
  Symbol
};

struct Token {
  std::string value;
  Type type;
  
  Token(std::string _value, Type _type){
    value = _value;
    type = _type;
  }
};

#endif
