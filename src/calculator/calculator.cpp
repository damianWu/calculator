// Copyright [2022] <@damianWu>

#include "calculator/calculator.hpp"

#include <stdexcept>

#include "token/token.hpp"

namespace {
void throw_exception(const std::string& error_msg, char token = ' ') {
    throw std::runtime_error(error_msg + token);
}
}  // namespace

namespace calculator {

using token::Token;

double primary() {
    Token token{get_token()};

    switch (token.kind) {
        case '8': {
            return token.value;
        }
        case '(': {
            double number{expression()};
            Token closing_token{get_token()};
            if (closing_token.kind == ')') {
                return number;
            }
            throw_exception(
                "Function calculator::primary() throws unexpected token "
                "exception! Escpected ')', but was ",
                closing_token.kind);
        }
    }
    throw_exception(
        "Function calculator::primary() throws"
        "unexpected token exception ",
        token.kind);
    return 0.0;
}

double term() {
    double left{primary()};

    while (true) {
        Token token{get_token()};

        switch (token.kind) {
            case '*': {
                left *= primary();
                break;
            }
            case '/': {
                double prim{primary()};
                if (compare_double(prim, 0)) {
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

bool compare_double(const double a, const double b) {
    double epsilon = std::numeric_limits<double>::epsilon();
    return std::abs(a - b) < epsilon;
}

}  // namespace calculator
