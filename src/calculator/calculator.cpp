// Copyright [2022] <@damianWu>

#include "calculator/calculator.hpp"

#include <stdexcept>

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
            case '/': {
                double prim{primary()};
                if (prim == 0) {  // TODO(@damianWu) poor verification
                    throw std::runtime_error(
                        "Function calculator::term() throws dividing by zero "
                        "exception!");
                }
                left /= prim;
                break;
            }
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
