#include "lexer.h"

extern std::unordered_map<std::string, OperationType> defined;

const std::string Lexer::kString = "\"";
const std::string Lexer::kNumRegex = "[0-9.]";
const std::string Lexer::kLineBreak = "\n";
const std::string Lexer::kComment = "$";
const std::string Lexer::kSymbolRegex = "[a-zA-Z_0-9]";
const std::string Lexer::kOperatorRegex = "\\+|-|\\*|\\/|=|>|<|>=|<=|&|\\||%|!|\\^|\\(|\\)|\\.";

Lexer::Lexer(Stream *_stream)
{
  line_num = 0;
  stream = _stream;
  stream->Init();
}

bool Lexer::Matches(char ch, std::string expr)
{
  std::string target = "";
  target.push_back(ch);
  std::regex regexp(expr);
  return std::regex_match(target, regexp);
}

std::string Lexer::ScanRegex(std::string expr)
{
  std::string ret;
  ret.push_back(stream->Curr());

  while (Matches(stream->GetNext(), expr))
  {
    ret.push_back(stream->GetNext());
    stream->MoveNext();
  }

  return ret;
}
void Lexer::ScanLnBreak()
{
  while(Matches(stream->GetNext(), kLineBreak)){
    line_num++;
    stream->MoveNext();
  }
}
std::string Lexer::ScanString(char delim)
{
  std::string ret = "";
  while (stream->GetNext() != '\0')
  {
    stream->MoveNext();
    if (stream->Curr() == delim)
      return ret;
    ret.push_back(stream->Curr());
  }
  std::cerr << "Error: you opened a string that you did not close at line " << line_num << ".\n";
  std::exit(0);
  return ret;
}

void Lexer::IgnoreLine()
{
  while (stream->GetNext() != '\0')
  {
    stream->MoveNext();
    if (Matches(stream->Curr(), kLineBreak))
      return;
  }
}

std::vector<Token> Lexer::Tokenize()
{
  std::vector<Token> tokens;

  while (stream->GetNext() != '\0')
  {
    stream->MoveNext();
    char curr = stream->Curr();
    if (curr == -1)
    {
      tokens.push_back(Token("EOF", END, NONE));
      break;
    }
    else if (curr == ' ')
      continue;
    else if (curr == '"')
      tokens.push_back(Token(ScanString('"'), STRING, NONE));
    else if (Matches(curr, kNumRegex))
      tokens.push_back(Token(ScanRegex(kNumRegex), NUMBER, NONE));
    else if (Matches(curr, kLineBreak))
    {
      line_num++;
      ScanLnBreak();
      tokens.push_back(Token("LINEBREAK", LINEBREAK, NONE));
    }
    else if (Matches(curr, kComment))
      IgnoreLine();
    else if (Matches(curr, kSymbolRegex))
    {
      std::string val = ScanRegex(kSymbolRegex);
      if (defined.find(val) != defined.end())
        tokens.push_back(Token(val, BUILTIN, defined[val]));
      else
        tokens.push_back(Token(val, SYMBOL));
    }
    else if (Matches(curr, kOperatorRegex))
    {
      std::string val = ScanRegex(kOperatorRegex);
      if (defined.find(val) != defined.end())
        tokens.push_back(Token(val, BUILTIN, defined[val]));
      else
      {
        std::cerr << "Error: unrecognized symbol \"" << val << "\" at line " << line_num << ".\n";
        exit(1);
      }
    }
    else
    {
      std::cerr << "Error: unrecognized symbol \"" << curr << "\" at line " << line_num << ".\n";
      exit(1);
    }
  }
  return tokens;
}
