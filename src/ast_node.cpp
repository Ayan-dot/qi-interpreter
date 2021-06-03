#include "ast_node.h"

const std::vector<std::unordered_set<std::string>> ASTNode::pre = {
    {"or"},
    {"and"},
    {"|"},
    {"^"},
    {"&"},
    {"==", "!="},
    {"<", "<=", ">", ">="},
    {">>", "<<"},
    {"+", "-"},
    {"*", "/", "%"},
    {"not"},
    {".", ",", "++", "--"},
    {"=", "-=", "+=", "*=", "/=", "%=", ">>=", "<<=", "&=", "|=", "^="},
    {"num", "str"},
};

const std::unordered_set<std::string> ASTNode::control = {
    "if",
    "elsif",
    "for",
    "while",
    "fn"};

ASTNode::ASTNode()
{
  children = std::vector<ASTNode>();
  op = Token();
}

ASTNode::ASTNode(std::vector<Token> tokens)
{
  /*
  [if, else, while, for, fn] expr 'start' 
   expr2*
  'end'

  list(tokens)
  1) check if line (look at back)
      ==> if line, then treat as expression
      ==> if it is not a line, then go to 2)
  2) it is not a line. figure which control type it is ...[if, else, while, for, fn]
  3) based on control type, contruct children structure
      e.g. for if statement children are:
      [condition, body]
       0,         1
  4) add children to children, initiliazing them
  5) yay.

  */
  /*  
  1) check if blocks exist
  2) if they do, divide into subblocks

    

  */
  std::cout << tokens[0].val << " " << tokens.back().val << "\n";

  if (tokens.size() == 1)
  {
    op = tokens[0];
    return;
  }

  bool has_break = false;
  for (Token &token : tokens)
  {
    if (token.token_type == LINEBREAK)
    {
      has_break = true;
      break;
    }
  }
  if (has_break)
  {
    tokens.push_back(Token("LINEBREAK", LINEBREAK, NONE));
    std::vector<std::pair<int, int>> blocks = GetBlocks(tokens);

    if (blocks.size() > 1 || (blocks.size() == 1 && control.find(tokens[blocks[0].first].val) == control.end() && has_break))
    {
      for (auto &block : blocks)
        children.push_back(ASTNode(SubArray(tokens, block.first, block.second)));
      return;
    }

    if (control.find(tokens[0].val) != control.end())
    {
      int cond = 1;
      while (cond < tokens.size() && tokens[cond].val != "start")
      {
        cond++;
      }
      children.push_back(ASTNode(SubArray(tokens, 1, cond - 1)));

      int start = blocks[0].first;
      int end = blocks[0].second;
      while (start < end && tokens[start].val != "start")
        ++start;
      children.push_back(ASTNode(SubArray(tokens, start + 2, end - 1)));
    }
  }

  else
  {
    int min_pre = 15, min_pre_index = -1;
    for (int i = 0; i < tokens.size(); ++i)
    {
      for (int j = 0; j < pre.size(); ++j)
      {
        if (pre[j].find(tokens[i].val) != pre[j].end())
        {
          if (j < min_pre)
          {
            min_pre = j;
            min_pre_index = i;
          }
        }
      }
    }

    if (min_pre_index == -1)
    {
      std::cerr << "Error: ?";
      exit(1);
    }

    op = tokens[min_pre_index];
    switch (op.operation_type)
    {
    case UNARY:
      if (min_pre_index != 0)
      {
        std::cerr << "Error: operation \"" << op.val << "\" not supported here.";
        exit(1);
      }
      else
        children.push_back(ASTNode(SubArray(tokens, min_pre_index + 1, tokens.size() - 1)));
      break;
    case BINARY:
      if (min_pre_index == 0 || min_pre_index == tokens.size() - 1)
      {
        std::cerr << "Error: operation \"" << op.val << "\" not supported here.";
        exit(1);
      }
      else
      {
        children.push_back(ASTNode(SubArray(tokens, 0, min_pre_index - 1)));
        children.push_back(ASTNode(SubArray(tokens, min_pre_index + 1, tokens.size() - 1)));
      }
      break;
    default:
      std::cerr << "Error: operation \"" << op.val << "\" not supported here.";
      exit(1);
      break;
    }
  }

  // std::vector<std::pair<int, int>> blocks = GetBlocks(tokens);

  // if (!blocks.empty())
  //   for (std::pair<int, int> &block : blocks)
  //     std::cout << block.first << ": " << tokens[block.first].val << ", " << block.second << ": " << tokens[block.second].val << "\n";
}

/*
0: if, 14: end
16: myN, 18: 10
20: fn, 59: end
61: for, 69: end
71: if, 80: end
*/

std::vector<std::pair<int, int>> ASTNode::GetBlocks(std::vector<Token> &tokens)
{
  std::vector<std::pair<int, int>> blocks;
  int count = tokens.size(), curr = 0;

  while (curr < count && tokens[curr].token_type != END)
  {
    int start = curr;
    while (curr < count && tokens[curr].token_type != END && tokens[curr].token_type != LINEBREAK && tokens[curr].val != "start")
      ++curr;
    if (curr == count || tokens[curr].token_type == END)
    {
      std::cerr << "Error: reached EOF while parsing file.";
      exit(1);
    }
    else if (tokens[curr].token_type == LINEBREAK)
    {
      blocks.push_back(std::make_pair(start, curr - 1));
      ++curr;
      continue;
    }
    else
    {
      int depth = 1;
      ++curr;
      while (curr < count && tokens[curr].token_type != END && !(tokens[curr].val == "end" && depth == 1))
      {
        if (tokens[curr].val == "start")
          ++depth;
        if (tokens[curr].val == "end")
          --depth;
        ++curr;
      }
      if (curr == count || tokens[curr].token_type == END)
      {
        std::cerr << "Error: reached EOF while parsing file.";
        exit(1);
      }
      else
      {
        blocks.push_back(std::make_pair(start, curr));
        ++curr;
      }
    }
    if (curr < count && tokens[curr].token_type == LINEBREAK)
      ++curr;
    else
    {
      std::cout << ((curr < count) ? tokens[curr].val : std::to_string(count)) << " " << tokens[curr - 1].val << "\n";
      std::cerr << "Error: invalid formatting error.";
      exit(1);
    }
  }

  return blocks;
}

std::vector<Token> ASTNode::SubArray(std::vector<Token> &arr, int i, int j)
{
  return std::vector<Token>(arr.begin() + i, arr.begin() + j + 1);
}
