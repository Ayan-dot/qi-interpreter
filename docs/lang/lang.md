# Qi Language and Syntax Reference

This section of the documentation is meant to act as a reference guide while using the language. The essential building blocks of the language are described as completely as possible, with usage examples for most built-ins. 

### 1. Introduction:

The Qi language is high level, weakly typed interpreted programming language. The language is interpreted in C++, supplemented by an executable cmd/shell command. The language does not contain object oriented programming frameworks at the moment, but contains all required utility to execute traditional linear programs in an effective and concise manner. 



### 2. Lexical Elements

#### **1. Tokens and supported characters**

​	Qi files contain text that consists of specific tokens and whitespace: tokens are essentially the smallest blocks of code within a .qi file that is comprehensible to the interpreter. These tokens can be grouped into the following categories: 

- Number and boolean literals

- String/character literals

- User-defined identifiers 

- Built-in keyword

- Operators

- Comments

  

In addition to these tokens, a .qi file can contain *whitespace* and *linebreaks*, both of which serve distinct purposes with respect to code structure. 



​	All Qi code must be written in compliance with the character set of the language: the lexer within the qi interpreter scans the file for a specific set of characters prior to categorization and symbols outside this defined set will throw `unrecognized symbol` errors. The supported character set at the moment is given below: 

```
A B C D E F G H I J K L M N O P Q R S T U V W X Y Z
```

```
a b c d e f g h i j k l m n o p q r s t u v w x y z 
```

```
0 1 2 3 4 5 6 7 8 9
```

```
. , ^ ! % & < = > / * + - $ " 
```

​	Although the lexer can recognize all these symbols, there are specific sequences of characters that purvey proper syntax and this is covered in later sections. Do note that as the qi interpreter does not have a corresponding IDE, syntax errors cannot be detected at compile-time. 

​	Some important character distinctions to make are the linebreak character `\n` that is scanned by the lexer at compile-time, and the EOF character `\0` that appears at the end of the file, signifying the end of stream input. These characters are essentially invisible but are extremely important in program structure and can cause issues with code compilation should they appear in misplaced contexts. 

#### 2. Number and boolean literals:

​	Number literals are literals used in arithmetic expressions, declarations, and countless other contexts in the Qi programming language. The syntax for non-decimal (integer) and decimal number literals are restricted by a **regular expression**. Specifically, integer literals can only contain characters within the bounds of `0-9`, whereas decimal literals can contain the decimal points `.` exactly once during the number. Below are some examples of number literals: 

```
3 | 75  |  320.0 |  .2  | 2901381902832901 | 0.00002020 |
9 | 630 | 4312.67|  42. |   1231239.1312   |  12129.12  |
```

Do note that both leading and trailing zeros are allowed in number literals. The behavior of leading zeros on numerical output will essentially convert the direct number literal to `0.xxx` , whereas trailing zeros will be interpreted as `X.0` and will be treated as such. 

Negative numbers are not parsed within these literals, the `-` operator is given both binary and unary functionality and thus negative numbers can be evaluated via a base expression instead.

#### 3. **String / Character Literals: **

​	The Qi language distinguishes between **symbols** and **string literals** via the use of of quotes; that is, a string must be surrounded by quotes `"` on either side of the string that restrict the value of the string to the sequence of characters present inside the quotes. The character set is the same as defined above. 

​	In Qi, there are only two special cases pertaining to string literals: the newline character `\n` which appends a line break to the string, and the delimiter `" ` character. In either case, the unwanted characters `n` and `"` are ignore via the use of the backslash `\` as a delimiter inside the string. 

Below are some examples of string literals: 

```
"qi language" | "awjdjk21h4j1kn321" | "111" | "\"qi\\nlanguage\"" | "\n" | "...+2"
```

In the case of the backslash delimiter appearing prior to an unrecognized special character, the sequence is unaltered and present in the final string literal. 

#### 4. User-defined identifiers:

​	A user-defined identifier can be used in Qi to define both variable names of different data types and function names. The characters that are permissible to include in an identifier are shown below:

```
a b c d e f g h i j k l m n o p q r s t u v w x y z 
A B C D E F G H I K L L M N O P Q R S T U V W X Y Z 
_ 0 1 2 3 4 5 6 7 8 9
```

Do note that numeric characters cannot be used at the front of an identifier (as the first character). 

#### 5. Built-in Keywords:

​	The Qi language contains a set of restricted symbols/keywords that have special meaning within the interpreter. These keywords are not to be used as identifiers as they are classified differently by the lexer. The list of restricted keywords is shown below:

```
and   else    end       for   of      num   map    none   rand
not   elsif   break     in   outl     str   set    floor  
or    else    continue  out  return   bool  queue  ceil
if    start   while     in    fn      arr   stack  round 
```

#### 6. Operators:

Some characters are read by the interpreter and considered operators; these operators can be of various different types including (but not limited to) comparison, arithmetic, bitwise, and assignment. In the prior section, some of the keywords are treated as and executed as operators, but the lexer has a specific regex for operators which is used to define the total list of syntactic operators as shown below:

```
+   **   <   >  <<   +=   //=  &=  (
-   //   <=  |   %   *=   %=   |=  )
*   ==   >=  &   =   **=  >>=  ^=  . 
/   !=   ^   >>  -=  /=   >>=  ,  
```

These operators are used in combination with identifiers and literals to evaluate expressions that denote the values of various elements in the program. Each operator has its own associativity and precedence, both of which are discussed in a later section. 

#### 7. Comments:

Comments are text in a .qi file that the interpreter scans but ignores; they are meant to be notes or messages for programmers themselves. A Qi comment is denoted by a `$` character which prompts the lexer to ignore all tokens and characters that occur on the same line. This applies to any sequence of characters and tokens. Do note that comments cannot be nested within literals. 

### 3. Data Handling

#### 1. Variable & Data Typing

​	The typing of a Qi variable has the effect of defining what the variable can and cannot do; not only are certain operators only available for specific types of variables, but some have built in methods and   thereby different implementations. Qi is strongly typed, and thus implicit conversion between types is not allowed as would be in a weakly typed counterpart. Variables purvey a value, and should this value be changeable, the variable is said to be mutable. There are specific objects / variables which contain **other** object types; for example the array, or `arr` variable. Typing impacts all functionality in Qi, and declaration of a variable without explicit typing is not allowed. Below is a table specifying the various basic types present in qi, and their corresponding functionality and sizes:  



| Type | Size    | Functionality                                                |
| ---- | ------- | ------------------------------------------------------------ |
| none | N/A     | Used to signify the absence of a value.                      |
| num  | 8 bytes | Used to signify real numbers with machine level implementation. |
| bool | 1 byte  | Used to signify the truth values, can only be 1 of two values |
| str  | N/A     | Used to signify string or character literals, sequenced character values. |

 The `num` variable: holds the value of an equivalent C++ `double` object and/or valid number literal. The representation of `num` is done in base 10. The range of the `num` variable spans from approximately    5.0x10<sup>-345</sup> to 1.7x10<sup>308</sup>.  The string representation of this value returns an integer with no trailing or leading decimal points if the value evaluates to one, or a general floating point number with unset precision. 

 The `str` variable: holds the value of an equivalent C++ `std::string` object and/or valid character literal. It is in effect a sequence and is treated as such in the implementation. 

The `bool`variable holds the value of an equivalent C++ `bool`object and contains a value that is restricted to either `True` or `False`, also denoted by `0` and  `1` .  The string representation of this variable returns either `0` or `1` , depending on the held value. 

Aside from these base types, Qi also contains various data structures or mutable sequences that are classified as below:

The `arr` type, or the Qi array holds a series or list of objects that can be composed of base types. Do note that in Qi, arrays can be composed of varying types including `num`, `str`, and even other `arr` types. These types can be mixed and match and there is no restriction on maintaining constant type inside the array. It is critical to note, however, that some type methods can only be called on `arr` types with the same type of objects inside. The string representation of this sequence would be square brackets that surround comma separated string representations of all child elements: 

```
[2, 4, "qi", 55]
```

The `queue` types and `stack` types are both fundamentally similar to the `arr` type in their containment schemes, but differ in the manner by which the contained data is entered and is structured. Both types correspond with their C++ counterparts. The `queue` sequence allows for objects to be pushed to the back of the queue and popped from the front (similar to a queue in real life). The `stack` sequence allows objects to be pushed on top of the stack, and then popped from the top as well; in effect removing the most recent element. Both types do not have a corresponding string representation. 

The `set` type in Qi is a sequence that is similar to an `arr`, but only holds unique elements in no particular order, allowing for fast retrieval of items based on hashed value searches. 

The `map` type in Qi is a sequence that is similar to an `arr`, but holds unique key value pairs that can be of different types. As an associative container, a map is similar to a `set` in that fast retrieval of items can be allowed via hashing, although the key is used to uniquely identify the element rather than the mapped value hash. 

#### 2. Built-in methods

Qi types can invoke various functions that are used as utility (such as sorting, searching, arithmetic rounding) via methods that corresponding to specific types, all uniquely named. For each type, the methods have unique behavior and the functionality of a method may not be supported for every type. Generally, methods can be called using prefix notation, calling the method via the dot `.` operator and the method name. The template for method calls is shown below:

```
identifier.method()
```

**Numeric methods: `num`**

- `floor()` - returns the floating point `num`value of the calling `num` rounded down. 
- `ceil()` - - returns the floating point `num`value of the calling `num` rounded up.
- `round(num)` - takes an unsigned integer `num` value as a parameter and returns the calling `num` rounded to the specified precision in the argument.

**String methods: `str`**

- `len()` - returns the `num` value of the length of the string, indexed by character. 
- `empty()`- returns a `bool` value evaluating to true if the string is empty (contains no characters).
- `find(str)` - returns the `num` value of the index of the `str` argument found in the calling `str` .  If the argument is not found, returns `-1`
- `reverse()` - returns the reverse of the calling `str`. 
- `at(num)` - returns the 1-length string present at the `num` index passed in the calling `str`. 
- `last()`-  returns the 1-length string at the final index of the calling `str`
- `pop()` - erases the final character in the calling `str`. 
- `sub(num, num, num)` - takes 3 `num` parameters corresponding with start index, end index, and step. Returns `str` value of substring corresponding to arguments. 
- `clear()` - erases the calling `str`. 
- `sort()` - sorts the calling `str` in alphabetical order. 

 



