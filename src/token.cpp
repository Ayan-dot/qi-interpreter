#include "token.h"

std::unordered_map<std::string, OperationType> defined;

Token::Token()
{
  val = "\0";
  token_type = UNDEFINED;
  operation_type = NONE;
}

Token::Token(std::string _val, TokenType _token_type)
{
  val = _val;
  token_type = _token_type;
  operation_type = NONE;
}

Token::Token(std::string _val, TokenType _token_type, OperationType _operation_type)
{
  val = _val;
  token_type = _token_type;
  operation_type = _operation_type;
}

Token::Token(char _val, TokenType _token_type)
{
  val = std::to_string(_val);
  token_type = _token_type;
  operation_type = NONE;
}

Token::Token(char _val, TokenType _token_type, OperationType _operation_type)
{
  val = std::to_string(_val);
  token_type = _token_type;
  operation_type = _operation_type;
}

void Token::Init()
{
  defined.insert(std::make_pair("+", BINARY));
  defined.insert(std::make_pair("-", BINARY));
  defined.insert(std::make_pair("*", BINARY));
  defined.insert(std::make_pair("/", BINARY));
  defined.insert(std::make_pair("==", BINARY));
  defined.insert(std::make_pair("!=", BINARY));
  defined.insert(std::make_pair("<", BINARY));
  defined.insert(std::make_pair("<=", BINARY));
  defined.insert(std::make_pair(">", BINARY));
  defined.insert(std::make_pair(">=", BINARY));
  defined.insert(std::make_pair("^", BINARY));
  defined.insert(std::make_pair("|", BINARY));
  defined.insert(std::make_pair(">>", BINARY));
  defined.insert(std::make_pair("<<", BINARY));
  defined.insert(std::make_pair("%", BINARY));
  defined.insert(std::make_pair("=", BINARY));
  defined.insert(std::make_pair("-=", BINARY));
  defined.insert(std::make_pair("+=", BINARY));
  defined.insert(std::make_pair("*=", BINARY));
  defined.insert(std::make_pair("/=", BINARY));
  defined.insert(std::make_pair("%=", BINARY));
  defined.insert(std::make_pair(">>=", BINARY));
  defined.insert(std::make_pair("<<=", BINARY));
  defined.insert(std::make_pair("&=", BINARY));
  defined.insert(std::make_pair("|=", BINARY));
  defined.insert(std::make_pair("^=", BINARY));
  defined.insert(std::make_pair(",", BINARY));
  defined.insert(std::make_pair("and", BINARY));
  defined.insert(std::make_pair("not", UNARY));
  defined.insert(std::make_pair("or", BINARY));
  defined.insert(std::make_pair("if", TERTIARY));
  defined.insert(std::make_pair("start", NONE));
  defined.insert(std::make_pair("end", NONE));
  defined.insert(std::make_pair("break", NONE));
  defined.insert(std::make_pair("continue", NONE));
  defined.insert(std::make_pair("while", BINARY));
  defined.insert(std::make_pair("for", BINARY));
  defined.insert(std::make_pair("of", BINARY));
  defined.insert(std::make_pair("in", UNARY));
  defined.insert(std::make_pair("out", BINARY));
  defined.insert(std::make_pair("num", UNARY));
  defined.insert(std::make_pair("bool", UNARY));
  defined.insert(std::make_pair("str", UNARY));
  defined.insert(std::make_pair("arr", UNARY));
  defined.insert(std::make_pair("fn", DYNAMIC));
  defined.insert(std::make_pair("(", NONE));
  defined.insert(std::make_pair(")", NONE));
}
