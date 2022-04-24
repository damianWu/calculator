// Copyright [2022] <@damianWu>

#include "calculator/calculator.hpp"

#include "token/token.hpp"

namespace calculator {

using token::Token;

double expression() {
    double left{term()};
    Token token{get_token()};

    switch (token.kind) {
        case '+':
            return left + term();
        case '-':
            return left - term();
        default:
            return left;
    }
}

}  // namespace calculator
