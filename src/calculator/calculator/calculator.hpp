// Copyright [2022] <@damianWu>
#ifndef SRC_CALCULATOR_CALCULATOR_CALCULATOR_HPP_
#define SRC_CALCULATOR_CALCULATOR_CALCULATOR_HPP_

#include <cstdint>
#include <string>
#include <vector>

#include "token/token.hpp"
#include "token_stream/token_stream.hpp"

namespace variables {

struct Variable {
    std::string name{};
    double value{};
    bool is_const{};
};

class SymbolTable {
 public:
    double get(const std::string& name);
    void set(const std::string& name, double value);

    bool is_declared(const std::string& variable_name);
    double define(const std::string& variable_name, double value,
                  bool is_const = false);

 private:
    std::vector<Variable> vars{};
};

}  // namespace variables

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
constexpr char DECL_KEY[]{"let"};
constexpr char CONST_KEY[]{"const"};
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

uint64 factorial(uint64 number);
bool compare_double(double a, double b);

}  // namespace calculator

#endif  // SRC_CALCULATOR_CALCULATOR_CALCULATOR_HPP_
