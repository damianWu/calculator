// Copyright [2022] <@damianWu>

#include "calculator/calculator.hpp"

#include <cmath>
#include <iostream>
#include <limits>
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

inline void throw_runtime_exception(const std::string& error_msg,
                                    const char token = '\0') {
    throw std::runtime_error(error_msg + token);
}

}  // namespace

namespace calculator {

using token::Token;

// Handle parenthesis, braces, factorial, logical not, bitwise not, negatie
// sign, positive sign and numbers
double primary() {
    Token token{ts.get()};

    switch (token.kind) {
        case FLOATING_POINT_NUMBER: {
            return verify_factorial(token.value);
        }
        case OPEN_PARENTHESIS: {
            double number{bitwise_or()};

            verify_closing_bracket(CLOSE_PARENTHESIS);
            number = verify_factorial(number);

            return number;
        }
        case OPEN_BRACE: {
            double number{bitwise_or()};

            verify_closing_bracket(CLOSE_BRACE);
            number = verify_factorial(number);

            return number;
        }
        case NEGATIVE_SIGN: {
            return -primary();
        }
        case POSITIVE_SIGN: {
            return primary();
        }
        case LOGICAL_NOT: {
            return logical_not();
        }
        case BITWISE_NOT: {
            return bitwise_not();
        }
        default:
            throw_runtime_exception(
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
                    throw_runtime_exception(
                        "Function calculator::term() "
                        "throws division by zero exception!");
                }
                left /= prim;
                break;
            }
            case '%': {
                double right{primary()};
                if (compare_double(right, 0.0)) {
                    throw_runtime_exception(
                        "Function calculator::term throws "
                        "modulo operator (%) division by zero exception.");
                }
                left = std::fmod(left, right);
                break;
            }
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

double bitwise_and() {
    double left{expression()};

    while (true) {
        // TODO(@damianWu) can token be inside while?
        Token token{ts.get()};

        switch (token.kind) {
            case '&':
                left = static_cast<double>(static_cast<uint64>(left) &
                                           static_cast<uint64>(expression()));
                break;
            default:
                ts.put_back(token);
                return left;
        }
    }
}

double bitwise_xor() {
    double left{bitwise_and()};

    while (true) {
        // TODO(@damianWu) can token be inside while?
        Token token{ts.get()};

        switch (token.kind) {
            case '^':
                left = static_cast<double>(static_cast<uint64>(left) ^
                                           static_cast<uint64>(bitwise_and()));
                break;
            default:
                ts.put_back(token);
                return left;
        }
    }
}

double bitwise_or() {
    double left{bitwise_xor()};

    while (true) {
        // TODO(@damianWu) can token be inside while?
        Token token{ts.get()};

        switch (token.kind) {
            case '|':
                left = static_cast<double>(static_cast<uint64>(left) |
                                           static_cast<uint64>(bitwise_xor()));
                break;
            default:
                ts.put_back(token);
                return left;
        }
    }
}

double calculate() {
    double result{};
    while (std::cin) {
        try {
            // std::cout << PROMPT;
            Token token{ts.get()};

            skip_print_symbol(&token);

            if (token.kind == EXIT) {
                return result;
            }

            ts.put_back(token);
            result = bitwise_or();

            if (is_token_floating_point_number(&token)) {
                throw_runtime_exception(
                    "Function calculator::calculate() "
                    "throws unexpected token exception. Syntax error. "
                    "No floating point literal expected.");
            }

            std::cout << RESULT << result << '\n';
        } catch (const std::exception& e) {
            std::cerr << "Exception catch in calculator::calculate() function "
                         "with message: "
                      << e.what() << '\n';
            clean_up_mess();
        } catch (...) {
            std::cerr << "Unknown type of exception catch in "
                         "calculator::calculate() function"
                      << '\n';
        }
    }
    throw_runtime_exception(
        "Function calculate::calculate() throws exception: "
        "reached unexpected program fragment. Expected retrun value by while "
        "loop.");
    return std::numeric_limits<double>::max();
}

void clean_up_mess() { ts.ignore(PRINT); }

void skip_print_symbol(Token* token) {
    while (token->kind == PRINT) {
        *token = ts.get();
    }
}

bool is_token_floating_point_number(Token* token) {
    *token = ts.get();
    if (token->kind == FLOATING_POINT_NUMBER) {
        return true;
    }
    ts.put_back(*token);
    return false;
}

void verify_closing_bracket(const char closing_bracket) {
    Token closing_token{ts.get()};
    if (closing_token.kind != closing_bracket) {
        std::string error_msg{
            "Function calculator::verify_closing_bracket() throws unexpected "
            "token exception! Expected "};
        (error_msg += closing_bracket) += (" but was: ");

        throw_runtime_exception(error_msg, closing_token.kind);
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

double logical_not() {
    double number{primary()};
    bool logical_number_value{static_cast<bool>(number)};
    return static_cast<double>(!logical_number_value);
}

double bitwise_not() {
    double number{primary()};
    uint64 number_integer{static_cast<uint64>(number)};
    return static_cast<double>(~number_integer);
}

bool compare_double(const double a, const double b) {
    double epsilon = std::numeric_limits<double>::epsilon();
    return std::abs(a - b) < epsilon;
}

}  // namespace calculator
