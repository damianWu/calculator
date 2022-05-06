// Copyright [2022] <@damianWu>
#ifndef SRC_CALCULATOR_CALCULATOR_CALCULATOR_HPP_
#define SRC_CALCULATOR_CALCULATOR_CALCULATOR_HPP_

#include <array>
#include <string>

#include "token/token.hpp"
#include "token_stream/token_stream.hpp"

namespace calculator {

using uint64 = std::uint64_t;

constexpr char OPEN_PARENTHESIS{'('};
constexpr char CLOSE_PARENTHESIS{')'};
constexpr char CLOSE_BRACE{'}'};
constexpr char OPEN_BRACE{'{'};

// Symbolizes floating-point (numeric) kind of token
constexpr char FLOATING_POINT_NUMBER{'8'};
// Finish program symbol
constexpr char EXIT{'x'};
// End of input expression symbol
constexpr char PRINT{';'};

constexpr char LOGICAL_NOT{'!'};
constexpr char BITWISE_NOT{'~'};
constexpr char NEGATIVE_SIGN{'-'};
constexpr char POSITIVE_SIGN{'+'};

constexpr char RESULT[]{"= "};

namespace grammar {

double primary();
double bitwise_not();
double logical_not();
double term();
double expression();
double bitwise_and();
double bitwise_xor();
double bitwise_or();
double statement();

}  // namespace grammar

double calculate();

bool is_factorial(const token::Token& token);
double verify_factorial(double number);
void verify_closing_bracket(char closing_bracket);

void clean_up_mess();
void skip_print_symbol(token::Token* token);
bool is_token_floating_point_number(token::Token* token);
void throw_if_get_floating_point_token();

uint64 factorial(uint64 number);
bool compare_double(double a, double b);

}  // namespace calculator

#endif  // SRC_CALCULATOR_CALCULATOR_CALCULATOR_HPP_
