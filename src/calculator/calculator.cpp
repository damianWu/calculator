// Copyright [2022] <@damianWu>

#include "calculator/calculator.hpp"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <iterator>
#include <limits>
#include <stdexcept>

#include "token/token.hpp"
#include "token_stream/token_stream.hpp"

using token_stream::TokenStream;

namespace {

// Receive, hold (only one) and give out token
TokenStream ts{};

inline void throw_runtime_exception(const std::string& error_msg,
                                    const char token = '\0') {
    throw std::runtime_error(error_msg + token);
}

}  // namespace

namespace variables {

std::vector<Variable> vars{};

// Return value of variable
double get_value(const std::string& name) {
    auto var_iterator{
        std::find_if(std::begin(vars), std::end(vars),
                     [&name](const Variable& v) { return name == v.name; })};
    if (var_iterator == std::end(vars)) {
        throw std::runtime_error(
            "double variables::get_value() throws exception. "
            "Unknow variable: " +
            name);
    }
    return var_iterator->value;
}

// Set value of (existing) variable
void set_value(const std::string& name, const double value) {
    auto var_iterator{std::find_if(
        std::begin(vars), std::end(vars),
        [&name](const Variable& var) { return name == var.name; })};
    if (var_iterator == std::end(vars)) {
        throw std::runtime_error(
            "double variables::set_value() throws exception. "
            "Unknow variable: " +
            name);
    }
    var_iterator->value = value;
}

bool is_declared(const std::string& variable_name) {
    auto var_iterator{std::find_if(std::begin(vars), std::end(vars),
                                   [&variable_name](const Variable& var) {
                                       return variable_name == var.name;
                                   })};
    return var_iterator != std::end(vars);
}

void define_name(const std::string& variable_name, const double value) {
    variables::vars.push_back(variables::Variable{variable_name, value});
}

}  // namespace variables

namespace calculator {

using token::Token;

namespace grammar {

// Handle parenthesis, braces, factorial, logical not, bitwise not, negative
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

double logical_not() {
    double number{primary()};
    bool logical_number_value{static_cast<bool>(number)};
    return static_cast<double>(!logical_number_value);
}

double bitwise_not() {
    double number{primary()};
    int64 number_integer{static_cast<int64>(number)};
    return static_cast<double>(~number_integer);
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

double declaration() {
    std::string variable_name{};
    std::cin >> variable_name;

    if (variables::is_declared(variable_name)) {
        throw std::runtime_error(
            "calculator::declaration() "
            " throws duplicate variable exception.");
    }

    Token token{ts.get()};
    if (token.kind == '=') {
        double value{calculator::grammar::bitwise_or()};
        variables::define_name(variable_name, value);
        return value;
    }
    throw_runtime_exception(
        "calculator::declaration() "
        " throws syntax error. Equal sign required, but was: ",
        token.kind);
    return 0.0;
}

double statement() {
    Token token{ts.get()};
    switch (token.kind) {
        case LET:
            return declaration();
        default: {
            ts.put_back(token);
            return bitwise_or();
        }
    }
}

}  // namespace grammar

using grammar::statement;

// Calculator starting point
// Allows you to perform multiple calculations in one run
double calculate() {
    double result{};
    while (std::cin) {
        try {
            Token token{ts.get()};

            skip_print_symbol(&token);

            if (token.kind == EXIT) {
                return result;
            }

            ts.put_back(token);
            result = statement();

            token = ts.get();
            throw_if_unexpected_token(token);
            ts.put_back(token);

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
    throw std::runtime_error(
        "Function calculate::calculate() throws exception: "
        "reached unexpected program fragment. Expected retrun value by while "
        "loop. Program forced to exit (probably).");
}

bool is_factorial(const Token& token) { return token.kind == '!'; }

double verify_factorial(const double number) {
    Token token{ts.get()};
    if (is_factorial(token)) {
        return static_cast<double>(factorial(static_cast<uint64>(number)));
    }
    ts.put_back(token);
    return number;
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

void clean_up_mess() { ts.ignore(PRINT); }

void skip_print_symbol(Token* token) {
    while (token->kind == PRINT) {
        *token = ts.get();
    }
}

bool is_token_floating_point_number(const Token& token) {
    return token.kind == FLOATING_POINT_NUMBER;
}

void throw_if_unexpected_token(const Token& token) {
    // Two token are unexpected at this stage: fp-number and bitwise not.
    // Reason #1: !3!2 = !(3!)2 = !62 ? What is two? 62? There is no operator
    //            between !6 and 2. Error!
    // Reason #2: ~3~2 = -4~2 -> -4 -3? Two numbers, no operator between them.
    if (is_token_floating_point_number(token) || token.kind == BITWISE_NOT) {
        throw_runtime_exception(
            "Function calculator::throw_if_unexpected_token() "
            "throws syntax error exception. No floating point literal "
            "or bitwise not expected.");
    }
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
