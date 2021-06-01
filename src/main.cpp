#include <iostream>
#include <string>
#include <vector>

#include "stream.h"
#include "token.h"
#include "lexer.h"

int main(int argc, char *argv[])
{
  if (argc == 1 || argc > 2)
    throw "Error: invalid argument count.";

  std::string file_name(argv[1]);
  if (file_name.size() < 4 || file_name.substr(file_name.size() - 3) != ".qi")
    std::cerr << "Error: invalid file name.";

  Token::Init();
  Stream *stream = new Stream(file_name);
  Lexer *lexer = new Lexer(stream);
  std::vector<Token> tokens = lexer->Tokenize();

  for (const Token &token : tokens)
    std::cout << "<Token val: " << token.val << ", type: " << token.token_type << ", op: " << token.operation_type << ">\n";
  return 0;
}