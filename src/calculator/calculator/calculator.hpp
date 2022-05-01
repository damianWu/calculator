// Copyright [2022] <@damianWu>
#ifndef SRC_CALCULATOR_CALCULATOR_CALCULATOR_HPP_
#define SRC_CALCULATOR_CALCULATOR_CALCULATOR_HPP_

#include <array>
#include <string>

#include "token/token.hpp"
#include "token_stream/token_stream.hpp"

namespace calculator {

// Symbolizes floating-point (numeric) kind of token
constexpr char TOKEN_KIND_OF_FLOATING_POINT_NUMBER{'8'};
// Finish program symbol
constexpr char EXIT{'x'};
// End of input expression symbol
constexpr char END_OF_EXPRESSION{';'};
// Prompt symbols
constexpr char PROMPT[]{"= "};

double calculate();

double expression();
double term();
double primary();

void verify_closing_bracket(const char closing_bracket);
bool compare_double(const double a, const double b);

}  // namespace calculator

#endif  // SRC_CALCULATOR_CALCULATOR_CALCULATOR_HPP_
