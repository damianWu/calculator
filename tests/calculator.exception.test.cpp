// Copyright [2022] <@damianWu>

#include "calculator/calculator.hpp"

#include <gtest/gtest.h>

#include <stdexcept>

#include "token/token.hpp"

namespace {

TEST(ExceptionCalculator_throw_if_unexpected_token_Function,
     ShouldThrowUnexpectedTokenRuntimeException_1) {
    EXPECT_THROW(
        {
            try {
                // Given
                token::Token token(calculator::FLOATING_POINT_NUMBER, 2);

                // When
                calculator::throw_if_unexpected_token(token);
            } catch (const std::runtime_error& e) {
                EXPECT_STREQ(
                    "Function calculator::throw_if_unexpected_token() "
                    "throws syntax error exception. No floating point literal "
                    "or bitwise not expected.",
                    e.what());
                throw;
            }
        },
        std::runtime_error);
}

TEST(ExceptionCalculator_throw_if_unexpected_token_Function,
     ShouldThrowUnexpectedTokenRuntimeException_2) {
    EXPECT_THROW(
        {
            try {
                // Given
                token::Token token('~');

                // When
                calculator::throw_if_unexpected_token(token);
            } catch (const std::runtime_error& e) {
                EXPECT_STREQ(
                    "Function calculator::throw_if_unexpected_token() "
                    "throws syntax error exception. No floating point literal "
                    "or bitwise not expected.",
                    e.what());
                throw;
            }
        },
        std::runtime_error);
}
////////////////////////////////////////////////////////////////////////////////
TEST(ExceptionCalculatorCalculateUnexpectedFragment,
     ShouldThrowRuntimeException_1) {
    EXPECT_THROW(
        {
            // Given
            std::istringstream input("\0");
            std::cin.rdbuf(input.rdbuf());
            try {
                // When
                calculator::calculate();
            } catch (const std::runtime_error& e) {
                EXPECT_STREQ(
                    "Function calculate::calculate() throws exception: "
                    "reached unexpected program fragment. Expected retrun "
                    "value by while "
                    "loop. Program forced to exit (probably).",
                    e.what());
                throw;
            }
        },
        std::runtime_error);
}
////////////////////////////////////////////////////////////////////////////////

}  // namespace
