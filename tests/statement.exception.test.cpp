// Copyright [2022] <@damianWu>
#include <gtest/gtest.h>

#include <stdexcept>

#include "calculator/calculator.hpp"

namespace {

TEST(ExceptionCalculationModuloOperator,
     ShouldThrowRuntimeModuloDivisionByZeroException_1) {
    EXPECT_THROW(
        {
            // Given
            std::istringstream input("6%0+1; x");
            std::cin.rdbuf(input.rdbuf());
            try {
                // When
                calculator::grammar::statement();
            } catch (const std::runtime_error& e) {
                EXPECT_STREQ(
                    "Function calculator::term throws "
                    "modulo operator (%) division by zero exception.",
                    e.what());
                throw;
            }
        },
        std::runtime_error);
}

TEST(ExceptionCalculationDivisionOperator,
     ShouldThrowRuntimeDivisionByZeroException_1) {
    EXPECT_THROW(
        {
            // Given
            std::istringstream input("22/0+1; x");
            std::cin.rdbuf(input.rdbuf());
            try {
                // When
                calculator::grammar::statement();
            } catch (const std::runtime_error& e) {
                EXPECT_STREQ(
                    "Function calculator::term() "
                    "throws division by zero exception!",
                    e.what());
                throw;
            }
        },
        std::runtime_error);
}

}  // namespace
