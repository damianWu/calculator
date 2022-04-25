// Copyright [2022] <@damianWu>

#include "token/token.hpp"

namespace token {

Token::Token(char ch) : kind(ch) {}
Token::Token(char ch, double val) : kind{ch}, value{val} {}

}  // namespace token
