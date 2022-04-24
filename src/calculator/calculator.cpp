// Copyright [2022] <@damianWu>

#include "calculator/calculator.hpp"

#include "token/token.hpp"

namespace calculator {

using token::Token;

double term() {
    double left{primary()};

    while (true) {
        Token token{get_token()};

        switch (token.kind) {
            case '*':
                left *= primary();
                break;
            case '/':
                left /= primary();
                break;
            // case '%':
            //     left = left % primary();
            //     break;
            default:
                return left;
        }
    }
}

double expression() {
    double left{term()};

    while (true) {
        Token token{get_token()};

        switch (token.kind) {
            case '+':
                left += term();
                break;
            case '-':
                left -= term();
                break;
            default:
                return left;
        }
    }
}

}  // namespace calculator
