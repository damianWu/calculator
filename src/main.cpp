// Copyright [2022] <@damianWu>

#include <iostream>

#include "calculator/calculator.hpp"
#include "token/token.hpp"
#include "token_stream/token_stream.hpp"

using uint32 = uint32_t;
using uint64 = uint64_t;
using int64 = int64_t;

using calculator::expression;
using token::Token;
using token_stream::TokenStream;

extern TokenStream ts;  // TODO(@damianWu) Should TokenStream be here?

namespace {

// Finish program
constexpr char EXIT{'x'};
constexpr char END_OF_EXPRESSION{';'};

}  // namespace

int main() {
    try {
        double val{};

        while (std::cin) {
            Token t{ts.get()};

            if (t.kind == 'k') {
                break;
            }

            if (t.kind == ';') {
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
