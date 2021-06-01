#include "stream.h"
#include <iostream>
#include <stdlib.h>

Stream::Stream()
{
  file_name = "";
  stream = new StreamNode();
}

Stream::Stream(std::string _file_name)
{
  std::ifstream f(_file_name);
  if (f.good())
    file_name = _file_name;
  else
  {
    std::cerr << "Error: file does not exist.";
    exit(1);
  }
  f.close();
  stream = new StreamNode();
}

void Stream::Init()
{
  std::ifstream feed(file_name);
  char curr;
  StreamNode *head = stream;
  while (feed.good())
  {
    curr = feed.get();
    head->next = new StreamNode(curr);
    head = head->next;
  }
}

char Stream::GetNext() const
{
  return stream->next ? stream->next->val : '\0';
}

char Stream::Curr() const
{
  return stream->val;
}

void Stream::MoveNext()
{
  if (stream->next)
    stream = stream->next;
  else
    throw "Error: no characters in stream.";
}