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

// read a token from cin
Token get_token() {
    char ch;
    std::cin >>
        ch;  // note that >> skips whitespace (space, newline, tab, etc.)

    switch (ch) {
            // not yet   case ';':    // for "print"
            // not yet   case 'q':    // for "quit"
        case '(':
        case ')':
        case '+':
        case '-':
        case '*':
        case '/':
            return Token(ch);  // let each character represent itself
        case '.':
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9': {
            std::cin.putback(ch);  // put digit back into the input stream
            double val;
            std::cin >> val;         // read a floating-point number
            return Token('8', val);  // let '8' represent "a number"
        }
        default:
            throw std::runtime_error(
                "calculator::get_token() throws exception: "
                "Bad token");
    }
}

}  // namespace calculator
