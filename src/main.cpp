// Copyright [2022] <@damianWu>

#include <iostream>

#include "calculator/calculator.hpp"
#include "token/token.hpp"

using uint32 = uint32_t;
using uint64 = uint64_t;
using int64 = int64_t;

using token::Token;

int main() {
    try {
    } catch (const std::exception &e) {
        std::cerr << "Exception catch in main function with message: "
                  << e.what() << '\n';
    } catch (...) {
        std::cerr << "Unknown type of exception catch in main function" << '\n';
    }
    return 0;
}
