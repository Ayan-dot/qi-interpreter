#ifndef TOKEN_H_INCLUDED
#define TOKEN_H_INCLUDED

#include <string>

enum Type {
  LineBreak,
  Operator,
  Punctuation,
  Number,
  Control,
  Symbol,
  String
};

struct Token {
  std::string val;
  Type type;
  Token(std::string _val, Type _type);
};

#endif
