#include <iostream>
#include <string>
#include <vector>

#include "stream.h"
#include "token.h"
#include "lexer.h"

int main(int argc, char* argv[]) {
  if (argc == 1 || argc > 2)
    throw "Error: invalid argument count.";
  
  std::string file_name(argv[1]);
  if (file_name.size() < 4 || file_name.substr(file_name.size() - 3) != ".qi")
    throw "Error: invalid file name.";

  Lexer* lexer = new Lexer(file_name);
  std::vector<Token> tokens = lexer->Tokenize();
  
  return 0;
}
