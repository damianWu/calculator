// Copyright [2022] <@damianWu>

#include <iostream>

#include "calculator/calculator.hpp"

using uint32 = uint32_t;
using uint64 = uint64_t;
using int64 = int64_t;

int main() {
    try {
        const auto result{calculator::calculate()};
        std::cout << "result: " << result << '\n';
    } catch (const std::exception &e) {
        std::cerr << "Exception catch in main function with message: "
                  << e.what() << '\n';
    } catch (...) {
        std::cerr << "Unknown type of exception catch in main function" << '\n';
    }
    return 0;
}
