// Copyright [2022] <@damianWu>
#ifndef SRC_TOKEN_TOKEN_TOKEN_HPP_
#define SRC_TOKEN_TOKEN_TOKEN_HPP_

namespace token {

struct Token {
    char kind;
    double value{};
    // make a Token from a char
    explicit Token(char ch) : kind(ch) {}
    // make a Token from a char and a double
    Token(char ch, double val) : kind{ch}, value{val} {}
};

}  // namespace token

#endif  // SRC_TOKEN_TOKEN_TOKEN_HPP_
