# `qlang` grammar

## 1 Introduction

`qlang` is a high level, weakly typed programming language, interpreted in C++ that
focuses on core imperative programming paradigms.

## 2 Tokens

### 2.1 Supported character set

Tokens are the smallest blocks of a `qlang` program from the perspective of the
interpreter. A token will must be one of the following:

1. Number or boolean literal
2. String or character literal
3. User-defined identifier
4. Built-in keyword
5. Operator
6. Comment block

Whitespace and line breaks are also important for syntax. Tokens are composed
from character combinations. Unquoted characters must match with `[A-Za-z0-9.,^!%&<=>/*+\-$"()\[\]{} ]`.
Otherwise, an `unrecognized symbol` error will be thrown.

### 2.2 Number or boolean literal

Decimal numbers are supported. Leading and trailing zeroes are allowed, but
ignored. Booleans are C-style booleans, where 0 evaluates to `false` and
everything else evaluates to `true`.

### 2.3 String or character literal

Symbols and string literals are distinguished by quotes. Characters surrounded
by quotes don't have to match with the `[A-Za-z0-9.,^!%&<=>/*+\-$"()\[\]{} ]`
regex for symbols. As with convention, the backslash character is used to mark
an escape sequence. Examples:

```bash
"qlang" | "awjdjk21h4j1kn321" | "111" | "\n" | "...+2"
```

In the case of the backslash delimiter appearing prior to an unrecognized
special character, the sequence is unaltered and present in the final string
literal.

### 2.4 User-defined identifiers

User-defined identifiers are used for variable and function declarations.
Identifiers must follow the `^[a-zA-Z][a-zA-Z0-9_]+$` regex (case sensitive
alphanumeric characters starting with an alphabetic character).

### 2.5 Built-in keywords

Built-in keywords are restricted symbols that have special meaning to the
interpreter. They cannot be reused as variable or function names. These
keywords are:

```
and   else    end        for   of       num    map     none    rand
not   elsif   break      in    outl     str    set     floor
or    else    continue   out   return   bool   queue   ceil
if    start   while      in    fn       arr    stack   round
```

### 2.6 Operators

Operators are use for expressions involving comparison, arithmetic, bitwise,
and assignment. Some built-in keywords are also treated like operators.
Lexically, the following tokens are recognized operators:

```
+   **   <    >    <<   +=    //=   &=   (
-   //   <=   |    %    *=    %=    |=   )
*   ==   >=   &    =    **=   >>=   ^=   .
/   !=   ^    >>   -=   /=    >>=   ,
```

### 2.7 Comments

Comments are text in a .q file that the interpreter scans but ignores. An
inline comment begins with the `$` character, prompting the lexer to ignore the
rest of the line. This applies to any sequence of characters and tokens. Note:
comments cannot be nested inside of literals.

## 3 Data types

### 3.1 Primitives

The typing of a `qlang` variable has the effect of defining what the variable can
and cannot do; not only are certain operators only available for specific types
of variables, but some have built in methods and thereby different
implementations. Some objects may contains other objects, for example variables
with type `arr`. Variables must be declared with a type. Below is a table
specifying the various basic types present in `qlang`, and their corresponding
functionality and sizes:

| Type | Size     | Functionality                            |
| ---- | -------- | ---------------------------------------- |
| none | 0 bytes  | denotes absence of a value               |
| num  | 8 bytes  | represents decimal numbers               |
| str  | flexible | represents a string of character literal |

- `num` supports base 10. Its underlying representation of a `double`.
- `str` has the underlying representation of a `std::string`.

Aside from these primitives, there are more complex objects:

- `arr`, for example `[2, 4, "qlang", 55]`, which is a list of objects that can be
  composed of any `qlang` variable. Note that some `arr` methods only apply to arrays
  with the same object type
- `queues` and `stacks` are represented by their C++ counterparts, and can hold
  any object type as with `arr`
- `sets` are hashable and unordered
- `maps` are similar to `arrs`, but keys can be `qlang` objects that are not natural
  numbers

### 3.2 Built-in methods

`qlang` types can invoke various functions that are used as utility (such as
sorting, searching, arithmetic rounding) via methods that corresponding to
specific types, all uniquely named. For each type, the methods have unique
behavior and the functionality of a method may not be supported for every type.
Generally, methods can be called using prefix notation, calling the method via
the dot `.` operator and the method name. The template for method calls is
shown below:

```
identifier.method()
```

**Numeric methods: `num`**

- `floor()` - returns the floating point `num`value of the calling `num`
  rounded down.
- `ceil()` - - returns the floating point `num`value of the calling `num`
  rounded up.
- `round(num)` - takes an unsigned integer `num` value as a parameter and
  returns the calling `num` rounded to the specified precision in the argument.

**String methods: `str`**

- `len()` - returns the `num` value of the length of the string, indexed by
  character.
- `empty()`- returns a `bool` value evaluating to true if the string is empty
  (contains no characters).
- `find(str)` - returns the `num` value of the index of the `str` argument
  found in the calling `str` . If the argument is not found, returns `-1`
- `reverse()` - returns the reverse of the calling `str`.
- `at(num)` - returns the 1-length string present at the `num` index passed in
  the calling `str`.
- `last()`- returns the 1-length string at the final index of the calling `str`
- `pop()` - erases the final character in the calling `str`.
- `sub(num, num, num)` - takes 3 `num` parameters corresponding with start
  index, end index, and step. Returns `str` value of substring corresponding to
  arguments.
- `clear()` - erases the calling `str`.
- `sort()` - sorts the calling `str` in alphabetical order.

**Array methods: `arr`**

- `len()` - returns the `num` value of the length of the array, indexed by
  element.
- `empty()`- returns a `bool` value evaluating to true if the array is empty
  (contains no elements).
- `find(|str, num|)` - returns the `num` value of the index of the `str / num`
  argument found in the calling `arr` . If the argument is not found, returns `-1`
- `reverse()` - returns the reverse of the calling `arr`.
- `at(num)` - returns the element present at the `num` index passed in the
  calling `arr`.
- `last()`- returns the element at the final index of the calling `arr`
- `push(|str, num, arr, bool|)`- pushes the object in the parameter as an
  element to the calling `arr`. Indexes at final value in `arr`.
- `pop()` - erases the final character in the calling `str`.
- `sub(num, num, num)` - takes 3 `num` parameters corresponding with start
  index, end index, and step. Returns `arr` value of subarray corresponding to
  arguments.
- `clear()` - erases the calling `arr`.
- `sort()` - sorts the calling `arr` in alphanumeric order. Note that this only
  works on `arr` structures with constant element types.
- `fill(num, num, |str, num, arr, bool|)` - Takes 2 `num` parameters and 1
  abstract parameter. Fills calling `arr` from start to end index with abstract
  argument.

**Queue methods: `queue`**

- `len()` - returns the `num` value of the length of the queue, indexed by
  element.
- `empty()`- returns a `bool` value evaluating to true if the queue is empty
  (contains no elements).
- `last()`- returns the element at the end of the calling `queue`.
- `next()` - returns the element at the front of the calling `queue`.
- `push(|str, num, arr, bool|)`- pushes the object in the parameter as an
  element to the calling `queue`. Indexes at the back of the `queue`.
- `pop()` - erases the front element in the calling `queue`.
- `clear()` - erases the calling `queue`.

**Stack methods: `stack`**

- `len()` - returns the `num` value of the length of the stack, indexed by
  element.
- `empty()`- returns a `bool` value evaluating to true if the stack is empty
  (contains no elements).
- `next()` - returns the element at the front of the calling `stack`.
- `push(|str, num, arr, bool|)`- pushes the object in the parameter as an
  element to the calling `stack`. Indexes at the top of the `stack`.
- `pop()` - erases the top element in the calling `stack`.
- `clear()` - erases the calling `stack`.

<!--add set and map-->

## 4 Program Model

Programs are read by the interpreter as blocks. `qlang` enforces the following
logical model for all programs

```
$ start of file

$ global variable definitions
 num x_global
 x_global = 2
 str y_global
 y = "globalvar"
 global variable definitions END

$ non-main function definitions
 fn square num (num a) start
 	return a**2
 end
$ non-main function definitions END

$ main function definition
 fn main none () start
 	num b
 	b = x_global
 	b = square(b)
 	out b
 end
$ main function definition END

$ end of file
```

The global variables **must** be defined before function definitions are, and
the **mandatory** main function must be declared after all functions and
variables have been declared.

### 4.1 Naming and scoping

`qlang` has memory environments that handle scoping and naming. Variable names must be unique withing each scope.

The scope of a variable defines the locations in the code where it can be referenced and changed. For example, for the following code:

```bash
num x
x = 20

fn square num (num a) start
	return a ** 2
end

fn main none () start
	num y
	y = 24
	out x_glob
end
```

`x` is global, because it is defined outside any function block. `y` is local to the `main` function and cannot be referenced outside of that scope.

### 4.2 Function definitions

The syntax for declaring a function is demonstrated below:

```
fn my_fn num (num b, num c) start
	if b == c start
		return b
	end
	return b + c
end

fn main none () start
	outl my_fn(1, 2) $ prints 3
end
```

In general, functions are defined as:

```
fn fn_name_in_global_scope return_type (arg1_type arg1, ...) start
	body
end
```

A general function call is:

```
fn_name(arg1, ...)
```

### 4.3 Variable declarations

Example syntax for variable declarations is shown below:

```
str x
x = "qlang"
num y
y = 2021
arr arr1
```

Note: assignment and declaration are independent.

### 4.4 Expressions

The `qlang` interpreter is required to go through the source code and build a tree
with parent and child nodes that can be used to the model the structure of the
code. Expressions can include any of the following:

- Identifiers / Literals
- Calls
- Operators

The combination of these effectively creates the body of the `qlang` program, and dictates how actions are taken and what exactly the program does in essence.
