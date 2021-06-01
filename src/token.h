#ifndef TOKEN_H_
#define TOKEN_H_

#include <string>
#include <unordered_map>

/*
it allows O(1) lookup time for built-in and O(1) reference to op type
unordered_map<str, OperationType>
*/

enum TokenType
{
  UNDEFINED, // 0
  STRING,    // 1
  NUMBER,    // 2
  LINEBREAK, // 3
  COMMENT,   // 4
  END,       // 5
  SYMBOL,    // 6
  BUILTIN    // 7
};

enum OperationType
{
  NONE,
  UNARY,
  BINARY,
  TERTIARY,
  DYNAMIC
};

class Token
{
public:
  std::string val;
  TokenType token_type;
  OperationType operation_type;

  Token();
  Token(std::string _val, TokenType _token_type);
  Token(std::string _val, TokenType _token_type, OperationType _operation_type);
  Token(char _val, TokenType _token_type);
  Token(char _val, TokenType _token_type, OperationType _operation_type);
  static void Init();
};

#endif
