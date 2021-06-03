#ifndef LEXER_H_
#define LEXER_H_

#include <iostream>
#include <regex>
#include <string>

#include "token.h"
#include "stream.h"

class Lexer
{
private:
  /*
-> string ==> "
read "
consume until " or throw err if linebreak

-> number ==> [0-9.]
read [0-9.]
consume until not [0-9.]

-> linebreak ==> \n
ignore / create new branch

-> single-line comment ==> $
read $
consume and discard until linebreak

-> end ==> EOF (non-regex)
end

-> symbol ==> [a-zA-z_0-9]
consume symbol while [a-zA-z_0-9]
=> check if symbol is built-in; if so, label as such

-> operator ==> (\+|-|\*|\/|=|>|<|>=|<=|&|\||%|!|\^|\(|\).) 
read = (/[\W\S_]/) // \W renives word chars so a-z, A-Z, 0-9 \S removes whitespace and _
consume operator while (/[\W\S_]/) applies
=> check if operator is built-in; if not, throw err
*/
  Stream *stream;
  int line_num;
  static const int checkEOF = EOF;
  static const std::string kString;
  static const std::string kNumRegex;
  static const std::string kLineBreak;
  static const std::string kComment;
  static const std::string kSymbolRegex;
  static const std::string kOperatorRegex;

public:
  Lexer(Stream *_stream);
  bool Matches(char ch, std::string expr);
  std::string ScanRegex(std::string expr);
  void ScanLnBreak();
  std::string ScanString(char delim);
  void IgnoreLine();
  std::vector<Token> Tokenize();
};

#endif // LEXER_H
