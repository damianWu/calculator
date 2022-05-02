# (Expression) Calculator

[//]: # (_The Last Markdown Editor, Ever_)

(Expression) Calculator compute seemingly simple expressions like: 8+20.5*2.
Expected value is 49. For humans is obvious, but think how we can program this idea
to be ''understandable'' by computers. Contrary to appearances it is not a trivial task.
To handle this problem we use idea of **tokens** and **grammars**.

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
    - 1 + 2 - 3
    - 3 * 2 + 4 / 2
- Handles negative numbers
- Handles modulo operator
- Variables
    - let var = 7.2;

## Usage
Run program and type correct mathematical expression using above features. Wait for result.
<!--## Installation-->
<!--## Plugins-->
<!--## Development-->
## License

MIT

**Free Software, Hell Yeah!**


[//]: # (These are reference links used in the body of this note and get stripped out when the markdown processor does its job. There is no need to format nicely because it shouldn't be seen. Thanks SO - http://stackoverflow.com/questions/4823468/store-comments-in-markdown-syntax)

   [github]: <https://github.com/damianWu>