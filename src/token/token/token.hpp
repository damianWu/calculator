// Copyright [2022] <@damianWu>
#ifndef SRC_TOKEN_TOKEN_TOKEN_HPP_
#define SRC_TOKEN_TOKEN_TOKEN_HPP_

namespace token {

struct Token {
    char kind;
    double value{};

    explicit Token(char ch);
    Token(char ch, double val);
};

}  // namespace token

#endif  // SRC_TOKEN_TOKEN_TOKEN_HPP_
