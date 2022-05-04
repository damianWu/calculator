// Copyright [2022] <@damianWu>

#include "token/token.hpp"

namespace token {

Token::Token(char k) : kind(k) {}
Token::Token(char k, double v) : kind{k}, value{v} {}

}  // namespace token
