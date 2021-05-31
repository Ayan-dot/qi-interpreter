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

  Node();
  Node(T _val);
  Node(T _val, Node* _next);
};

/*
 * A readable stream implementing the linked lits defined above to
 * read file characters and peek forward. 
 */
class Stream {
 private:
  Node<char> char_stream;
  std::string file_name;

 public:
  Stream();
  Stream(std::string file_name);
  void SetFileName();
  void Initialize();
  char Next() const;
  void MoveNext();
  ~Stream();
};

#endif // #ifndef STREAM_H_INCLUDED
