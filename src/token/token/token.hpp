// Copyright [2022] <@damianWu>
#ifndef SRC_TOKEN_TOKEN_TOKEN_HPP_
#define SRC_TOKEN_TOKEN_TOKEN_HPP_

#include <string>

namespace token {

struct Token {
    char kind{};
    double value{};
    std::string name{};

    explicit Token(char k);
    Token(char k, double v);
    Token(char k, const std::string& n);
};

}  // namespace token

#endif  // SRC_TOKEN_TOKEN_TOKEN_HPP_
