// Copyright [2022] <@damianWu>

#include "calculator/calculator.hpp"

#include <iostream>
#include <stdexcept>

#include "token_stream/token_stream.hpp"

using token_stream::TokenStream;

namespace {

// Receives, holds (only one) and give out token
TokenStream ts{};

constexpr char open_parenthesis{'('};
constexpr char close_parenthesis{')'};
constexpr char open_brace{'{'};
constexpr char close_brace{'}'};

inline void throw_exception(const std::string& error_msg,
                            const char token = ' ') {
    throw std::runtime_error(error_msg + token);
}

}  // namespace

namespace calculator {

using token::Token;

double calculate() {
    double val{};

    while (std::cin) {
        Token t{ts.get()};

        if (t.kind == EXIT) {
            break;
        }

        if (t.kind == END_OF_EXPRESSION) {
            std::cout << PROMPT << val << '\n';
        } else {
            ts.put_back(t);
        }

        val = expression();
    }
    return val;
}

// Handle parenthesis and numbers
double primary() {
    Token token{ts.get()};

    switch (token.kind) {
        case TOKEN_KIND_OF_FLOATING_POINT_NUMBER: {
            return token.value;
        }
        case open_parenthesis: {
            return execute_expr_verify_closing_bracket(close_parenthesis);
            break;
        }
        case open_brace: {
            return execute_expr_verify_closing_bracket(close_brace);
            break;
        }
        default:
            // ts.put_back(token);
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
                    throw_exception(
                        "Function calculator::term() "
                        "throws dividing by zero exception!");
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
        // TODO(@damianWu) can token be inside while?
        Token token{ts.get()};

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

double execute_expr_verify_closing_bracket(const char closing_bracket) {
    double number{expression()};
    Token closing_token{ts.get()};
    if (closing_token.kind == closing_bracket) {
        return number;
    }

    std::string error_msg{
        "Function calculator::primary() throws unexpected token "
        "exception! Escpected "};
    (error_msg += closing_bracket) += (" but was: ");

    throw_exception(error_msg, closing_token.kind);
    return 0;
}

bool compare_double(const double a, const double b) {
    double epsilon = std::numeric_limits<double>::epsilon();
    return std::abs(a - b) < epsilon;
}

}  // namespace calculator
