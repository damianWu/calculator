// Copyright [2022] <@damianWu>
#ifndef SRC_CALCULATOR_CALCULATOR_CALCULATOR_HPP_
#define SRC_CALCULATOR_CALCULATOR_CALCULATOR_HPP_

#include <limits>
#include <stdexcept>
#include <string>

#include "token/token.hpp"
#include "token_stream/token_stream.hpp"

namespace calculator {

using uint64 = std::uint64_t;
using int64 = std::int64_t;

// Symbolizes floating-point (numeric) kind of token
constexpr char FLOATING_POINT_NUMBER{'8'};
// Finish program symbol/token kind
constexpr char EXIT{'@'};
// End of input expression symbol/token kind
constexpr char PRINT{';'};
// variable name token kind
constexpr char VAR_NAME{'a'};
// let keyword token kind
constexpr char LET{'L'};
// const keyword token kind
constexpr char CONST{'C'};
// help token kink
constexpr char HELP{'H'};
constexpr char VERSION{'V'};

constexpr char OPEN_PARENTHESIS{'('};
constexpr char CLOSE_PARENTHESIS{')'};
constexpr char CLOSE_BRACE{'}'};
constexpr char OPEN_BRACE{'{'};
constexpr char EQUAL_SIGN{'='};

constexpr char LOGICAL_NOT{'!'};
constexpr char BITWISE_NOT{'~'};
constexpr char NEGATIVE_SIGN{'-'};
constexpr char POSITIVE_SIGN{'+'};

// Variable definition keyword
constexpr char DECL_KEYWORD[]{"let"};
// Const variable definition keyword
constexpr char CONST_KEYWORD[]{"const"};
constexpr char VERSION_KEYWORD[]{"V"};
constexpr char HELP_KEYWORD[]{"help"};

constexpr char RESULT[]{"= "};

namespace grammar {

double primary();
double bitwise_not();
double logical_not();
double term();
double expression();
double bitwise_and();
double bitwise_or();
double bitwise_xor();
double statement();
double declaration(const token::Token& var_type);

}  // namespace grammar

double calculate();

bool is_factorial(const token::Token& token);
double verify_factorial(double number);
void verify_closing_bracket(char closing_bracket);

void clean_up_mess();
void skip_print_symbol(token::Token* token);
bool is_token_floating_point_number(const token::Token& token);
void throw_if_unexpected_token(const token::Token& token);

void print_help_message();
void print_version_message();
bool compare_double(double a, double b);

constexpr uint64 factorial(const uint64 number) {
    if (number == 0) {
        return 1;
    }
    return number * factorial(number - 1);
}

inline bool compare_double(const double a, const double b) {
    double epsilon = std::numeric_limits<double>::epsilon();
    return std::abs(a - b) <= epsilon * std::abs(a);
}

inline void throw_runtime_exception(const std::string& error_msg,
                                    const char token = '\0') {
    throw std::runtime_error(error_msg + token);
}

}  // namespace calculator

#endif  // SRC_CALCULATOR_CALCULATOR_CALCULATOR_HPP_
