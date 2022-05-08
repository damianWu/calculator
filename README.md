# (Expression) Calculator

(Expression) The calculator compute seemingly simple expressions like: 8+20.5*2.
Expected value is 49. For humans is obvious, but think how we can program this idea
to be ''understandable'' by computers. Contrary to appearances it is not a trivial task.
To handle this problem we use idea of **tokens** and **grammars**.

The program is also an example how a **compiler works**. Program analyzes input broken
down into tokens and understood according to a grammar.

## Tokens and grammars
##### Tokens
A **token** is a sequence of characters that represents something we consider a unit, such
as a number or an operator. Assume that we despose Token type, we can express 
(2.5+19)*11 with seven tokens:

Token kind | '(' | '8' | '+' | '8' | ')' | '*' | '8' |
---        | --- | --- | --- | --- | --- | --- | --- |
Value      |     | 2.5 |     |  19 |     |     | 11  |

Token type '8' means floating-point-literal.

##### Grammar
For example, we know that 45+11.5/7 means 45+(11.5/7) and not (45+11.5)/7 , but how do we
teach the program that useful rule (division “binds tighter” than addition)? The standard
answer is that we write a **grammar** defining the syntax of our input and then write a program
that implements the rules of that grammar. For example:
```
Expression:
    Term
    Expression "+" Term
    Expression "-" Term
Term:
    Primary
    Term "*" Primary
    Term "/" Primary
    Term "%" Primary
Primary:
    Number
    "(" Expression ")"
Number:
    floating-point-literal
```

## Features
- Follows the order of the arithmetic operations
    - 8 + 20.5 * 2 = 8 + (20.5 * 2) = 8 + 41 = 49
    - 45 + 11.5 / 7 = 45 + (11.5 / 7) = 45 + 1.64 = 46.64 
    - 1 - 2 * 3 = 1 - (2 * 3) = 1 - 6 = -5
    - 1 + 2 - 3 = 3 - 3 = 0
    - 3 * 2 + 4 / 2 = 6 + 2 = 8
    - 2 * 3 * 4 = 6 * 4 = 24
    - 10 - 10 * 10 + 10 = 10 - 100 + 10 = -90 + 10 = -80
- Handles negative numbers
    - -1 / 2 = -0.5
    - -1 / -2 = 0.5
    - --2 = 2
- Handles modulo operator
    - 4 % 2 = 0
    - 1 % 6 = 1
- Variables and constants
    - let var = 7.2
    - const pi = 3.14159265359
- Factorial
    - 0! = 1
    - 4! = 24
    - 4*4! = 96
- Bitwise operators
    - 5 | 2 = 7
    - 5 ^ 6 = 3
    - 5 & 2 = 0
- Logical operators
    - !0 = 1
    - !82 = 0
- Compound expressions
    - 2 * 2 + 8 / 4 % 3 - 30 ^ 3 = -21
    - !24! - 1 = -1
    - !4! - 1 = !(4!) - 1 = !24 - 1 = 0 - 1 = -1
    - 23 | 43 - 1 ^ 54 & 32 = 31

## Usage
Run program and type correct mathematical expression (calculation unit) using above features.
Every calculation unit should be finished with print operator: ';'. For example:
```
8 + 20.5 * 2;
```
#### You can write multiple calculation units in one line.
Following input:
```
8 + 20.5 * 2; let pi = 3.1415; 2 * pi;
```
gives in result:
```
    = 49
    = 3.1415
    = 6.283
```
If you want to immediately exit program after making calculations, write '@' operator
at the end:
```
8 + 20.5 * 2; let pi = 3.1415; 2 * pi; @
```
Program prints result and exits.

## Program grammar
```
Calculation:
    Statement
    Version
    Help
    Print
    Quit
    Calculation Statement
Statement:
    Declaration
    Expression
Declaration:
    "let" Name "=" Expression
    "const" Name "=" Expression
Version:
    "V"
Help:
    "help"
Statement:
    BitwiseOR
    Print
    Quit
Print (end expression):
    ";"
Quit:
    "@"
BitwiseOR:
    BitwiseXOR
    BitwiseOR "|" BitwiseXOR
BitwiseXOR:
    BitwiseAND
    BitwiseXOR "^" BitwiseAND
BitwiseAND:
    Expression
    BitwiseAND "&" Expression
Expression:
    Term
    Expression "+" Term
    Expression "-" Term
Term:
    Primary
    Term "*" Primary
    Term "/" Primary
    Term "%" Primary
Primary:
    Number
    Name
    Name "=" Expression
    "(" Expression ")"
    "-" Primary
    "+" Primary
    Primary "!"
Number:
    floating-point-literal
Name:
    [a-zA-Z][a-zA-Z_0-9]
```
<!--## Installation-->
<!--## Plugins-->
<!--## Development-->

## Inspiration
The program is inspired by ideas from the great Bjarne Stroustrup's book [Programming -- Principles and Practice Using C++][ppp].

## License

MIT

[//]: # (These are reference links used in the body of this note and get stripped out when the markdown processor does its job. There is no need to format nicely because it shouldn't be seen. Thanks SO - http://stackoverflow.com/questions/4823468/store-comments-in-markdown-syntax)

   [github]: <https://github.com/damianWu>
   [ppp]: <https://www.stroustrup.com/programming.html>