#ifndef STREAM_H_INCLUDED
#define STREAM_H_INCLUDED

#include <fstream>
#include <iostream>
#include <string>

/**
 * A singly linked list implementation for the peekable stream used
 * to read characters from the file.
 */
template <typename T>
struct Node { 
  T val;
  Node *next;

  Node() {}
  Node(T _val) {
    val = _val;
  }
  Node(T _val, Node* _next) {
    val = _val;
    next = _next;
  }
};

/*
 * A readable stream implementing the linked lits defined above to
 * read file characters and peek forward. 
 */
class Stream {
 private:
  Node<char>* char_stream;
  std::string file_name;

 public:
  Stream();
  Stream(std::string _file_name);
  void SetFileName(std::string _file_name);
  void Init();
  char Next() const;
  char Cur() const;
  void MoveNext();
};

#endif // #ifndef STREAM_H_INCLUDED
