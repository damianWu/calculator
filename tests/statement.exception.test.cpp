// Copyright [2022] <@damianWu>
#include <gtest/gtest.h>

#include <iostream>
#include <stdexcept>

#include "calculator/calculator.hpp"

namespace {
// Exception tests
////////////////////////////////////////////////////////////////////////////////
// TEST(ExceptionCalculatorCalculateFunction, ShouldThrowRuntimeException_1) {
//     EXPECT_THROW(
//         {
//             try {
//                 // Given
//                 std::istringstream input("2!2");
//                 std::cin.rdbuf(input.rdbuf());

//                 // When
//                 calculator::calculate();
//             } catch (const std::runtime_error& e) {
//                 EXPECT_STREQ("", e.what());
//                 throw;
//             }
//         },
//         std::runtime_error);
// }
////////////////////////////////////////////////////////////////////////////////
// TEST(ExceptionTokenStreamTokenStreamGet, ShouldThrowRuntimeException_1) {
//     EXPECT_THROW(
//         {
//             // Given
//             std::istringstream input("2*2'");
//             std::cin.rdbuf(input.rdbuf());
//             try {
//                 // When
//                 calculator::statement();
//             } catch (const std::runtime_error& e) {
//                 EXPECT_STREQ(
//                     "token_stream::TokenStream::get() "
//                     "throws unknown token exception: '",
//                     e.what());
//                 throw;
//             }
//         },
//         std::runtime_error);
// }
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
                calculator::statement();
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
