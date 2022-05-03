// Copyright [2022] <@damianWu>
#ifndef SRC_CALCULATOR_CALCULATOR_CALCULATOR_HPP_
#define SRC_CALCULATOR_CALCULATOR_CALCULATOR_HPP_

#include <array>
#include <string>

#include "token/token.hpp"
#include "token_stream/token_stream.hpp"

namespace calculator {

using uint64 = std::uint64_t;

// Symbolizes floating-point (numeric) kind of token
constexpr char FLOATING_POINT_NUMBER{'8'};
// Finish program symbol
constexpr char EXIT{'x'};
// End of input expression symbol
constexpr char END_OF_EXPRESSION{';'};

constexpr char LOGICAL_NOT{'!'};
constexpr char BITWISE_NOT{'~'};
constexpr char NEGATIVE_SIGN{'-'};
constexpr char POSITIVE_SIGN{'+'};

constexpr char RESULT[]{"= "};
// constexpr char PROMPT[]{"> "};

double calculate();

double bitwise_xor();
double bitwise_or();
double bitwise_and();
double expression();
double term();
double primary();

bool is_factorial();
double verify_factorial(const double number);
uint64 factorial(const uint64 number);
void verify_closing_bracket(const char closing_bracket);

double bitwise_not();
double logical_not();

void skip_print_symbol(token::Token* token);
bool is_floating_point_number_token(token::Token* token);
bool compare_double(const double a, const double b);

}  // namespace calculator

#endif  // SRC_CALCULATOR_CALCULATOR_CALCULATOR_HPP_
