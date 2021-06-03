#include <iostream>
#include <string>
#include <vector>

#include "stream.h"
#include "token.h"
#include "lexer.h"
#include "ast_node.h"

int main(int argc, char *argv[])
{
  if (argc == 1 || argc > 2)
    throw "Error: invalid argument count.";

  std::string file_name(argv[1]);
  if (file_name.size() < 4 || file_name.substr(file_name.size() - 3) != ".qi")
    std::cerr << "Error: invalid file name: " << file_name << ".";

  Token::Init();
  Stream *stream = new Stream(file_name);
  Lexer *lexer = new Lexer(stream);
  ASTNode *ast = new ASTNode(lexer->Tokenize());

  return 0;
}
