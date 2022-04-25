// Copyright [2022] <@damianWu>
#ifndef SRC_CALCULATOR_CALCULATOR_CALCULATOR_HPP_
#define SRC_CALCULATOR_CALCULATOR_CALCULATOR_HPP_

// #include <string>

#include "token/token.hpp"

// Symbolizes floating-point (numeric) kind of token
constexpr static char TOKEN_KIND_OF_FLOATING_POINT_NUMBER{'8'};

namespace calculator {

using token::Token;

double expression();
double term();
double primary();

Token get_token();

bool compare_double(const double a, const double b);

}  // namespace calculator

#endif  // SRC_CALCULATOR_CALCULATOR_CALCULATOR_HPP_
