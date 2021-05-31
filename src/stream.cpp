#include "stream.h"

void Stream::SetFileName(std::string _file_name) {
  std::ifstream f(_file_name);
  if (!f.good())
    throw "Error: file does not exist.";

  f.close();
  file_name = _file_name;
}

Stream::Stream() {
  file_name = "";
  char_stream = new Node<char>();
}

Stream::Stream(std::string _file_name) {
  SetFileName(_file_name);
}

void Stream::Init() {
  std::ifstream input(file_name);
  char curr;
  Node<char>* head = char_stream;

  while (input.good()) {
    curr = input.get();
    head->next = new Node<char>(curr);
    head = head->next;
  }
}

char Stream::Next() const {
  return char_stream->next ? char_stream->next->val : '\0';
}

char Stream::Cur() const {
  return char_stream->val;
}

void Stream::MoveNext() {
  if (char_stream->next)
    char_stream = char_stream->next;
  else
    throw "Error: no characters in stream.";
}
