#ifndef LEXER_H_INCLUDED
#define LEXER_H_INCLUDED

#include "stream.h"
#include "token.h";

#include <regex>
#include <string>
#include <unordered_set>
#include <vector>

class Lexer {
 private:
  static const std::regex kNumRegex;
  static const std::regex kSymbolRegex;
  static const std::unordered_set<std::string> kOperators; 
  static const std::unordered_set<std::string> kString; 
  static const std::unordered_set<std::string> kPunctuation;
  static const std::unordered_set<std::string> kControl;

  Stream* file_stream;

 public:
  Lexer(std::string file_name);
  std::string ScanRegex(const std::regex format);
  std::string ScanSet(const std::unordered_set<std::string> keywords);
  std::string ScanString(const std::string delim);
  std::vector<Token> Tokenize();
};
 
#endif // #ifndef LEXER_H_INCLUDED
