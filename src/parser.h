#ifndef PARSER_H_
#define PARSER_H_

#include <string>
#include <vector>

#include "token.h"

class Parser
{
private:
  std::vector<Token> *tokens;
  int index;

public:
  Parser(std::vector<Token> _tokens);
  Token *GetToken(const int di);
  Token *GetToken();
  void SetIndex(const int _index);
};

#endif // PARSER_H_
