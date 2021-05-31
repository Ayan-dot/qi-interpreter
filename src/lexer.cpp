#include "lexer.h"

const std::regex Lexer::kNumRegex("\\[.0-9]");
const std::regex Lexer::kSymbolRegex("[_a-zA-Z0-9]");

const std::unordered_set<std::string> Lexer::kOperators = { ".", "++", "--", "not", "~", "*", "/", "%", "+", "–", "<<", ">>", "<", "<=", ">", ">=", "==", "!=", "&", "^", "|", "and", "or", "=", "–=", "+=", "*=", "/=", "%=", ">>=", "<<=", "&=", "|=", "^="};
const std::unordered_set<std::string> Lexer::kPunctuation = { "{", "}" , "(", ")", "$", "//", "start", "end"};
const std::unordered_set<std::string> Lexer::kControl = {"if", "else", "break", "continue", "while","for"};

Lexer::Lexer(std::string file_name) {
  file_stream = new Stream(file_name);
  file_stream->Init();
}

std::string Lexer::ScanRegex(const std::regex format) {
  std::string val = std::to_string(file_stream->Cur());
  while (std::regex_match(std::to_string(file_stream->Next()), format)) {
    val.push_back(file_stream->Next());
    file_stream->MoveNext();
  }
  return val;
}

std::string Lexer::ScanSet(const std::unordered_set<std::string> keywords) {
  std::string val = std::to_string(file_stream->Cur());
  while (keywords.find(std::to_string(file_stream->Next())) != keywords.end()) {
    val.push_back(file_stream->Next());
    file_stream->MoveNext();
  }
  return val;
}

std::string Lexer::ScanString(const std::string delim) {
  std::string val = "";
  while (std::to_string(file_stream->Next()) != delim) {
    val.push_back(file_stream->Next());
    file_stream->MoveNext();
  }
  file_stream->MoveNext();
  return val;
}

std::vector<Token> Lexer::Tokenize() {
  std::vector<Token> tokens;
  while (file_stream->Next() != '\0') {
    file_stream->MoveNext();
    char curr = file_stream->Cur();
    if (curr == ' ')
      continue;
    else if (curr == '\n')
      tokens.push_back(Token("\n", LineBreak));
    else if (kOperators.find(std::to_string(curr)) != kOperators.end())
      tokens.push_back(Token(ScanSet(kOperators), Operator));
    else if (kPunctuation.find(std::to_string(curr)) != kPunctuation.end())
      tokens.push_back(Token(ScanSet(kPunctuation), Operator));
    else if (std::regex_match(std::to_string(curr), kNumRegex))
      tokens.push_back(Token(ScanRegex(kNumRegex), Number));
    else
      throw "Error: Invalid character sequence.";
  }

  return tokens;
}
