// Copyright [2022] <@damianWu>
#ifndef SRC_CALCULATOR_CALCULATOR_CALCULATOR_HPP_
#define SRC_CALCULATOR_CALCULATOR_CALCULATOR_HPP_

// #include <string>

#include "token/token.hpp"

// namespace {
// void throw_exception(const std::string& error_msg, char token = ' ');
// }  // namespace

namespace calculator {

using token::Token;

double expression();
double term();
double primary();

Token get_token();

}  // namespace calculator

#endif  // SRC_CALCULATOR_CALCULATOR_CALCULATOR_HPP_
