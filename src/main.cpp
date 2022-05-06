// Copyright [2022] <@damianWu>

#include <iostream>

#include "calculator/calculator.hpp"

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
