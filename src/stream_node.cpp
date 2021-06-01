#include "stream_node.h"

StreamNode::StreamNode()
{
  val = '\0';
  next = nullptr;
}

StreamNode::StreamNode(char _val)
{
  val = _val;
  next = nullptr;
}

StreamNode::StreamNode(char _val, StreamNode *_next)
{
  val = _val;
  next = _next;
}
