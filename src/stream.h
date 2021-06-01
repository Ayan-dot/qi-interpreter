#ifndef STREAM_H_
#define STREAM_H_

#include <fstream>
#include <iostream>
#include <string>
#include "stream_node.h"

class Stream
{
private:
  StreamNode *stream;
  std::string file_name;

public:
  Stream();
  Stream(std::string _file_name);
  void Init();
  char Curr() const;
  char GetNext() const;
  void MoveNext();
};

#endif
