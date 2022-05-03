// Copyright [2022] <@damianWu>
#include "calculator/calculator.hpp"

#include <gtest/gtest.h>

#include <iostream>
#include <stdexcept>

namespace {
// Exception tests
////////////////////////////////////////////////////////////////////////////////
TEST(ExceptionCalculatorCalculateFunction, ShouldThrowRuntimeException_1) {
    EXPECT_THROW(
        {
            try {
                // Given
                std::istringstream input("2!2");
                std::cin.rdbuf(input.rdbuf());

                // When
                calculator::calculate();
            } catch (const std::runtime_error& e) {
                EXPECT_STREQ(
                    "Function calculator::calculate() "
                    "throws unexpected token exception. Syntax error. "
                    "No floating point literal expected.",
                    e.what());
                throw;
            }
        },
        std::runtime_error);
}

TEST(ExceptionCalculatorCalculateFunction, ShouldThrowRuntimeException_2) {
    EXPECT_THROW(
        {
            try {
                // Given
                std::istringstream input("2 2");
                std::cin.rdbuf(input.rdbuf());

                // When
                calculator::calculate();
            } catch (const std::runtime_error& e) {
                EXPECT_STREQ(
                    "Function calculator::calculate() "
                    "throws unexpected token exception. Syntax error. "
                    "No floating point literal expected.",
                    e.what());
                throw;
            }
        },
        std::runtime_error);
}

////////////////////////////////////////////////////////////////////////////////
TEST(ExceptionToken_streamTokenStreamGet, ShouldThrowRuntimeException_1) {
    EXPECT_THROW(
        {
            // Given
            std::istringstream input("2*2 '");
            std::cin.rdbuf(input.rdbuf());
            try {
                // When
                calculator::calculate();
            } catch (const std::runtime_error& e) {
                EXPECT_STREQ(
                    "token_stream::TokenStream::get() "
                    "throws unknown token exception: '",
                    e.what());
                throw;
            }
        },
        std::runtime_error);
}
////////////////////////////////////////////////////////////////////////////////
TEST(CorrectCalculationModuloOperator,
     ShouldThrowRuntimeModuloDivisionByZeroException_1) {
    EXPECT_THROW(
        {
            // Given
            std::istringstream input("6%0; x");
            std::cin.rdbuf(input.rdbuf());
            try {
                // When
                calculator::calculate();
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
////////////////////////////////////////////////////////////////////////////////

}  // namespace
