// Copyright [2022] <@damianWu>

#include "calculator/calculator.hpp"

#include <iostream>
#include <stdexcept>

#include "token/token.hpp"
#include "token_stream/token_stream.hpp"

using token_stream::TokenStream;

TokenStream ts;  // TODO(@damianWu) Should TokenStream be here?

namespace {
void throw_exception(const std::string& error_msg, char token = ' ') {
    throw std::runtime_error(error_msg + token);
}

}  // namespace

namespace calculator {

using token::Token;

// Handle parenthesis and numbers
double primary() {
    Token token{ts.get()};

    switch (token.kind) {
        case TOKEN_KIND_OF_FLOATING_POINT_NUMBER: {
            return token.value;
        }
        case '(': {
            double number{expression()};
            Token closing_token{ts.get()};
            if (closing_token.kind == ')') {
                return number;
            }
            throw_exception(
                "Function calculator::primary() throws unexpected token "
                "exception! Escpected ')', but was ",
                closing_token.kind);
            break;
        }
        default:
            throw_exception(
                "Function calculator::primary() throws "
                "unexpected token exception: ",
                token.kind);
    }
    return 0;
}

// Handle '*', '/' and '%' operators
double term() {
    double left{primary()};

    while (true) {
        Token token{ts.get()};

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
                ts.put_back(token);
                return left;
        }
    }
}

// Handle '+' and '-' operators
double expression() {
    double left{term()};

    while (true) {
        Token token{ts.get()};  // // TODO(@damianWu) can token be inside while?

        switch (token.kind) {
            case '+':
                left += term();
                break;
            case '-':
                left -= term();
                break;
            default:
                ts.put_back(token);
                return left;
        }
    }
}

bool compare_double(const double a, const double b) {
    double epsilon = std::numeric_limits<double>::epsilon();
    return std::abs(a - b) < epsilon;
}

}  // namespace calculator
