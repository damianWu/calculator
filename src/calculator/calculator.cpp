// Copyright [2022] <@damianWu>

#include "calculator/calculator.hpp"

#include <cmath>
#include <iostream>

#include "token/token.hpp"
#include "token_stream/token_stream.hpp"
#include "variables/variables.hpp"

namespace {

const char PROGRAM_VERSION[]{"1.0.0"};
const char AUTHOR[]{"https://github.com/damianWu"};

}  // namespace

namespace calculator {

using token::Token;
using token_stream::TokenStream;

// Receive, hold (only one) and give out token
TokenStream ts{};

namespace grammar {

// Holds and give access to all calculator variables
variables::SymbolTable st{};

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
        case VAR_NAME: {
            if (st.is_declared(token.name)) {
                Token t{ts.get()};
                if (t.kind == EQUAL_SIGN) {  // handle name = expression
                    double number{primary()};
                    st.set(token.name, number);
                    return number;
                }
                ts.put_back(t);  // not an assignment: return the value
                return st.get(token.name);
            }
            throw std::runtime_error(
                "calculator::primary() throws unknown variable name "
                "exception.");
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
                left = static_cast<double>(static_cast<int64>(left) &
                                           static_cast<int64>(expression()));
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
                left = static_cast<double>(static_cast<int64>(left) ^
                                           static_cast<int64>(bitwise_and()));
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
                left = static_cast<double>(static_cast<int64>(left) |
                                           static_cast<int64>(bitwise_xor()));
                break;
            default:
                ts.put_back(token);
                return left;
        }
    }
}

double declaration(const Token& var_type) {
    Token name_tkn{ts.get()};
    if (name_tkn.kind != VAR_NAME) {
        throw_runtime_exception(
            "calculator::declaration() throws syntax error. Variable name "
            "required.");
    }

    Token equal_sign_tkn{ts.get()};
    if (equal_sign_tkn.kind != EQUAL_SIGN) {
        throw_runtime_exception(
            "calculator::declaration() "
            " throws syntax error. Equal sign required in variable definition, "
            "but was: ",
            equal_sign_tkn.kind);
    }

    double value{calculator::grammar::bitwise_or()};
    st.define(name_tkn.name, value, var_type.kind == CONST);
    return value;
}

double statement() {
    Token token{ts.get()};
    switch (token.kind) {
        case LET:
        case CONST: {
            return declaration(token);
        }
        default: {
            ts.put_back(token);
            return bitwise_or();
        }
    }
}

}  // namespace grammar

// Calculator starting point
// Allows you to perform multiple calculations in program one run
double calculate() {
    double result{};
    while (std::cin) {
        try {
            Token token{ts.get()};

            skip_print_symbol(&token);

            if (token.kind == EXIT) {
                return result;
            }

            if (token.kind == HELP) {
                print_help_message();
                continue;
            }

            if (token.kind == VERSION) {
                print_version_message();
                continue;
            }

            ts.put_back(token);
            result = grammar::statement();

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

// Two token are unexpected at this stage: fp-number and bitwise not.
// Reason #1: !3!2 = !(3!)2 = !62 ? What is two? 62? There is no operator
//            between !6 and 2. Error!
// Reason #2: ~3~2 = -4~2 -> -4 -3? Two numbers, no operator between them.
void throw_if_unexpected_token(const Token& token) {
    if (is_token_floating_point_number(token) || token.kind == BITWISE_NOT) {
        throw_runtime_exception(
            "Function calculator::throw_if_unexpected_token() "
            "throws syntax error exception. No floating point literal "
            "or bitwise not expected.");
    }
}

void print_help_message() {
    std::cout << "calculator version " << PROGRAM_VERSION << '\n';
    std::cout << "Author:\t" << AUTHOR << "\n\n";
    std::cout << "USAGE:" << '\n';
    std::cout << "\tcalculator [FLAGS]" << '\n';
    std::cout << "\tcalculator [MATH EXPRESSION]" << '\n';
    std::cout << "FLAGS:" << '\n';
    std::cout << "\thelp\t\t Prints help information" << '\n';
    std::cout << "\tV\t\t Prints version information" << '\n';
    std::cout << "MATH EXPRESSION (end symbols):" << '\n';
    std::cout << "\t@\t\t Exits program" << '\n';
    std::cout << "\t;\t\t Ends every calculation" << '\n';
    std::cout << "\tlet <var-name> = <value>;\t\t Define variable" << '\n';
    std::cout << "\tconst <var-name> = <value>;\t\t Define constant variable"
              << '\n';
    std::cout << "MATH EXPRESSION (examples):" << '\n';
    std::cout << "\tEXPRESSION\t\t RESULT" << '\n';
    std::cout << "\t2+2*2; @\t\t 6" << '\n';
    std::cout << "\t(2+2)*2; @\t\t 8" << '\n';
    std::cout
        << "\tlet c = 12.00;\n\tlet z = 2*c;\n\tconst g = z; c = 1;\n\tc+z+g; @"
           "\t\t 49"
        << '\n';
}

void print_version_message() {
    std::cout << "calculator version " << PROGRAM_VERSION << '\n';
}

}  // namespace calculator
