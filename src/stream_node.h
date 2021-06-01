#ifndef STREAM_NODE_H_
#define STREAM_NODE_H_

/* Linked list implementation for a character stream. */
class StreamNode
{
public:
  char val;
  StreamNode *next;

  StreamNode();
  StreamNode(char _val);
  StreamNode(char _val, StreamNode *_next);
};

#endif
