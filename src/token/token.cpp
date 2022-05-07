// Copyright [2022] <@damianWu>

#include "token/token.hpp"

#include <string>

namespace token {

Token::Token(char k) : kind(k) {}
Token::Token(char k, double v) : kind{k}, value{v} {}

Token::Token(char k, const std::string& n) : kind(k), name(n) {}

}  // namespace token
