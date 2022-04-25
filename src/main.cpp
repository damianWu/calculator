// Copyright [2022] <@damianWu>

#include <iostream>

#include "calculator/calculator.hpp"
#include "token/token.hpp"
#include "token_stream/token_stream.hpp"

using uint32 = uint32_t;
using uint64 = uint64_t;
using int64 = int64_t;

using calculator::END_OF_EXPRESSION;
using calculator::EXIT;
using calculator::expression;
using calculator::PROMPT;
using calculator::ts;
using token::Token;

int main() {
    try {
        double val{};

        while (std::cin) {
            Token t{ts.get()};

            if (t.kind == EXIT) {
                break;
            }

            if (t.kind == END_OF_EXPRESSION) {
                std::cout << "= " << val << '\n';
            } else {
                ts.put_back(t);
            }

            val = expression();
        }
    } catch (const std::exception &e) {
        std::cerr << "Exception catch in main function with message: "
                  << e.what() << '\n';
    } catch (...) {
        std::cerr << "Unknown type of exception catch in main function" << '\n';
    }
    return 0;
}
