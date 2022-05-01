// Copyright [2022] <@damianWu>

#include "calculator/calculator.hpp"

#include <iostream>
#include <stdexcept>

#include "token/token.hpp"
#include "token_stream/token_stream.hpp"

using token_stream::TokenStream;

namespace {

constexpr char OPEN_PARENTHESIS{'('};
constexpr char CLOSE_PARENTHESIS{')'};
constexpr char CLOSE_BRACE{'}'};
constexpr char OPEN_BRACE{'{'};

// Receives, holds (only one) and give out token
TokenStream ts{};

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
            return verify_factorial(token.value);
        }
        case OPEN_PARENTHESIS: {
            double number{expression()};

            verify_closing_bracket(CLOSE_PARENTHESIS);
            number = verify_factorial(number);

            return number;
        }
        case OPEN_BRACE: {
            double number{expression()};

            verify_closing_bracket(CLOSE_BRACE);
            number = verify_factorial(number);

            return number;
        }
        case LOGICAL_NOT: {
            return calculate_logical_not();
        }
        case BITWISE_NOT: {
            return calculate_bitwise_not();
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

void verify_closing_bracket(const char closing_bracket) {
    Token closing_token{ts.get()};
    if (closing_token.kind != closing_bracket) {
        std::string error_msg{
            "Function calculator::verify_closing_bracket() throws unexpected "
            "token exception! Expected "};
        (error_msg += closing_bracket) += (" but was: ");

        throw_exception(error_msg, closing_token.kind);
    }
}

double verify_factorial(const double number) {
    if (is_factorial()) {
        return static_cast<double>(factorial(static_cast<uint64>(number)));
    }
    return number;
}

// TODO(@damianWu) To improve?
bool is_factorial() {
    Token token{ts.get()};
    if (token.kind == '!') {
        return true;
    }

    ts.put_back(token);
    return false;
}

uint64 factorial(const uint64 number) {
    if (number == 0) {
        return 1;
    }
    return number * factorial(number - 1);
}

bool compare_double(const double a, const double b) {
    double epsilon = std::numeric_limits<double>::epsilon();
    return std::abs(a - b) < epsilon;
}

}  // namespace calculator
