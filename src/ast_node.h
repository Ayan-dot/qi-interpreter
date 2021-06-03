#ifndef EXPR_H_
#define EXPR_H_

#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

#include "token.h"

class ASTNode
{
private:
  std::vector<ASTNode> children;
  static const std::vector<std::unordered_set<std::string>> pre;
  static const std::unordered_set<std::string> control;
  Token op;

public:
  ASTNode();
  ASTNode(std::vector<Token> tokens);
  static void Init();
  std::vector<std::pair<int, int>> GetBlocks(std::vector<Token> &tokens);
  std::vector<Token> SubArray(std::vector<Token> &arr, int i, int j);
};

/*
```
if condition start
  
end

num x = 7

num sq = x * x

out sq

simple: num y = 10


out y

if condition start
  num x = 7
  num cb = x * x * x
  out cb
end
```

1) check blocks
    a) iterate through tokens
    b) mark every start and end
    b.2) mark every unnested line break
    c) save them
    d) separate them

                              // blocks ==> conditional, function calls, 

4*5/2-1
 ^

idx 1 is OP
check OP n-ary ===> binary
1) tokens[:1] is first child
2) tokens[2:] is second child

*/

/*
vector<hashset<string> > pre;

======> tokens to initialize the expr

EXPR object
-> directly
statement direct (easy)

INPUT FILE:
(BEGIN)
fn factorial(num n) start
  if n == 0 start
    return 1
  end
  return n * factorial(n - 1)
end

fn main() start
  num x
  in x
  factorial(x)
end
(END)

block:
  inside of fn,
            if,
            loops

variable declaration
conditional
statement with operands 

  
  
  how do i evaluate a block
  how do i chain a block in a tree
  
a block is something with a `start` and an `end`
1) iterate through the block, noting all other start/end pairs and line breaks
2) each start/end pair is put into the child
3) each line break is another child (on the same level as start/end)
4) construct tree for these children
5) yay



basic math and operations --> EXPR


-> from EXPR (simple) because you just take the reminaing from left or right


5 + 5 * 6 - 10


0 --> highest pre
...
n --> lowest pre

>>> 5 * ((5 - 10) / ((2) * (factorial(10))))

IS TOKEN OPERATOR?
int highestPre, highestPreIndex

==> yes:
  iterate ..pre:
    is this highest pre?                                  
      store
    ignore

i know the position of the FIRST highest index

divide that based on N-ARY nature of the operator

recurse.

n) base case
==> 1 token
*/

#endif // EXPR_H_
