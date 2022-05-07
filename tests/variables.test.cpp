// Copyright [2022] <@damianWu>
#include <gtest/gtest.h>

#include <iostream>

#include "calculator/calculator.hpp"

namespace {

// class CalculatorFixture1 : public ::testing::TestWithParam<std::string> {};

// TEST_P(CalculatorFixture1, ShouldReturnExpectedResult_1) {
//     // Given
//     std::istringstream input(GetParam());
//     std::cin.rdbuf(input.rdbuf());
//     double expected{4.0};

//     // When
//     double given{calculator::calculate()};

//     // Then
//     ASSERT_NEAR(given, expected, 0.0001);
// }

// INSTANTIATE_TEST_SUITE_P(ExpectedResultTwoTest, CalculatorFixture1,
//                          ::testing::Values("2+2; x", "2*2; x", "4; x",
//                                            "20/5; x"));
////////////////////////////////////////////////////////////////////////////////
TEST(FindCorrectVariable, ShouldFindExpectedVariableValue_1) {
    // Given
    double expected{-3.0};

    // When
    double given{calculator::calculate()};

    FAIL();
    // Then
    ASSERT_NEAR(given, expected, 0.00001);
}
////////////////////////////////////////////////////////////////////////////////
}  // namespace
