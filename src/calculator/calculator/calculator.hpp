// Copyright [2022] <@damianWu>
#ifndef SRC_CALCULATOR_CALCULATOR_CALCULATOR_HPP_
#define SRC_CALCULATOR_CALCULATOR_CALCULATOR_HPP_

#include <array>
#include <string>

#include "token/token.hpp"
#include "token_stream/token_stream.hpp"

namespace calculator {
// extern token_stream::TokenStream ts;

// Symbolizes floating-point (numeric) kind of token
constexpr static char TOKEN_KIND_OF_FLOATING_POINT_NUMBER{'8'};
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

token::Token get_token();

bool compare_double(const double a, const double b);

}  // namespace calculator

#endif  // SRC_CALCULATOR_CALCULATOR_CALCULATOR_HPP_
