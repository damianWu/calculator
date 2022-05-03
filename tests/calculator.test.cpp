// Copyright [2022] <@damianWu>
#include "calculator/calculator.hpp"

#include <gtest/gtest.h>

#include <iostream>
#include <stdexcept>

namespace {

class CalculatorFixture1 : public ::testing::TestWithParam<std::string> {};

TEST_P(CalculatorFixture1, ShouldReturnExpectedResult_1) {
    // Given
    std::istringstream input(GetParam());
    std::cin.rdbuf(input.rdbuf());
    double expected{4.0};

    // When
    double given{calculator::calculate()};

    // Then
    ASSERT_NEAR(given, expected, 0.0001);
}

INSTANTIATE_TEST_SUITE_P(ExpectedResultTwoTest, CalculatorFixture1,
                         ::testing::Values("2+2; x", "2*2; x", "4; x",
                                           "20/5; x"));
////////////////////////////////////////////////////////////////////////////////
class CalculatorFixture2 : public ::testing::TestWithParam<std::string> {};

TEST_P(CalculatorFixture2, ShouldReturnExpectedResult_2) {
    // Given
    std::istringstream input(GetParam());
    std::cin.rdbuf(input.rdbuf());
    double expected{7.71429};

    // When
    double given{calculator::calculate()};

    // Then
    ASSERT_NEAR(given, expected, 0.00001);
}

INSTANTIATE_TEST_SUITE_P(ExpectedResultEqualTo7dot71429Test, CalculatorFixture2,
                         ::testing::Values("{(4+5)*6}/(3+4); x",
                                           "({4+5}*6)/(3+4); x",
                                           "({4+5}*6)/{3+4}; x"));
////////////////////////////////////////////////////////////////////////////////
TEST(CorrectCalculationTest, ShouldReturnExpectedResult_1) {
    // Given
    std::istringstream input("1-2-3; x");
    std::cin.rdbuf(input.rdbuf());
    double expected{-4.0};

    // When
    double given{calculator::calculate()};

    // Then
    ASSERT_NEAR(given, expected, 0.00001);
}

TEST(CorrectCalculationTest, ShouldReturnExpectedResult_2) {
    // Given
    std::istringstream input("280; x");
    std::cin.rdbuf(input.rdbuf());
    double expected{280.0};

    // When
    double given{calculator::calculate()};

    // Then
    ASSERT_NEAR(given, expected, 0.00001);
}

TEST(CorrectCalculationTest, ShouldReturnExpectedResult_3) {
    // Given
    std::istringstream input("3!*2*2; x");
    std::cin.rdbuf(input.rdbuf());
    double expected{24.0};

    // When
    double given{calculator::calculate()};

    // Then
    ASSERT_NEAR(given, expected, 0.00001);
}
////////////////////////////////////////////////////////////////////////////////
TEST(CorrectCalculationFactorialTest, ShouldReturnExpectedFactorialResult_1) {
    // Given
    std::istringstream input("0!; x");
    std::cin.rdbuf(input.rdbuf());
    double expected{1.0};

    // When
    double given{calculator::calculate()};

    // Then
    ASSERT_NEAR(given, expected, 0.00001);
}

TEST(CorrectCalculationFactorialTest, ShouldReturnExpectedFactorialResult_2) {
    // Given
    std::istringstream input("4!; x");
    std::cin.rdbuf(input.rdbuf());
    double expected{24.0};

    // When
    double given{calculator::calculate()};

    // Then
    ASSERT_NEAR(given, expected, 0.00001);
}

TEST(CorrectCalculationFactorialTest, ShouldReturnExpectedFactorialResult_3) {
    // Given
    std::istringstream input("8!; x");
    std::cin.rdbuf(input.rdbuf());
    double expected{40320.0};

    // When
    double given{calculator::calculate()};

    // Then
    ASSERT_NEAR(given, expected, 0.00001);
}

TEST(CorrectCalculationFactorialTest, ShouldReturnExpectedFactorialResult_4) {
    // Given
    std::istringstream input("2*3!; x");
    std::cin.rdbuf(input.rdbuf());
    double expected{12.0};

    // When
    double given{calculator::calculate()};

    // Then
    ASSERT_NEAR(given, expected, 0.00001);
}

TEST(CorrectCalculationFactorialTest, ShouldReturnExpectedFactorialResult_5) {
    // Given
    std::istringstream input("2*(3!); x");
    std::cin.rdbuf(input.rdbuf());
    double expected{12.0};

    // When
    double given{calculator::calculate()};

    // Then
    ASSERT_NEAR(given, expected, 0.00001);
}

TEST(CorrectCalculationFactorialTest, ShouldReturnExpectedFactorialResult_6) {
    // Given
    std::istringstream input("(2*3)!; x");
    std::cin.rdbuf(input.rdbuf());
    double expected{720.0};

    // When
    double given{calculator::calculate()};

    // Then
    ASSERT_NEAR(given, expected, 0.00001);
}
////////////////////////////////////////////////////////////////////////////////
TEST(CorrectCalculationBinaryNotTest, ShouldReturnExpectedBinaryNotResult_1) {
    // Given
    std::istringstream input("!(324); x");
    std::cin.rdbuf(input.rdbuf());
    double expected{0.0};

    // When
    double given{calculator::calculate()};

    // Then
    ASSERT_NEAR(given, expected, 0.00001);
}

TEST(CorrectCalculationBinaryNotTest, ShouldReturnExpectedBinaryNotResult_2) {
    // Given
    std::istringstream input("2*!(34); x");
    std::cin.rdbuf(input.rdbuf());
    double expected{0.0};

    // When
    double given{calculator::calculate()};

    // Then
    ASSERT_NEAR(given, expected, 0.00001);
}

TEST(CorrectCalculationBinaryNotTest, ShouldReturnExpectedBinaryNotResult_3) {
    // Given
    std::istringstream input("!(0); x");
    std::cin.rdbuf(input.rdbuf());
    double expected{1.0};

    // When
    double given{calculator::calculate()};

    // Then
    ASSERT_NEAR(given, expected, 0.00001);
}

TEST(CorrectCalculationBinaryNotTest, ShouldReturnExpectedBinaryNotResult_4) {
    // Given
    std::istringstream input("!(0)+1; x");
    std::cin.rdbuf(input.rdbuf());
    double expected{2.0};

    // When
    double given{calculator::calculate()};

    // Then
    ASSERT_NEAR(given, expected, 0.00001);
}

TEST(CorrectCalculationBinaryNotTest, ShouldReturnExpectedBinaryNotResult_5) {
    // Given
    std::istringstream input("!2+3; x");
    std::cin.rdbuf(input.rdbuf());
    double expected{3.0};

    // When
    double given{calculator::calculate()};

    // Then
    ASSERT_NEAR(given, expected, 0.00001);
}

TEST(CorrectCalculationBinaryNotTest, ShouldReturnExpectedBinaryNotResult_6) {
    // Given
    std::istringstream input("(!3)!; x");
    std::cin.rdbuf(input.rdbuf());
    double expected{1.0};

    // When
    double given{calculator::calculate()};

    // Then
    ASSERT_NEAR(given, expected, 0.00001);
}
////////////////////////////////////////////////////////////////////////////////
TEST(CorrectCalculationBitwiseXORTest, ShouldReturnExpectedBitwiseXORResult_1) {
    // Given
    std::istringstream input("(23^4)^54; x");
    std::cin.rdbuf(input.rdbuf());
    double expected{37.0};

    // When
    double given{calculator::calculate()};

    // Then
    ASSERT_NEAR(given, expected, 0.00001);
}

TEST(CorrectCalculationBitwiseXORTest, ShouldReturnExpectedBitwiseXORResult_2) {
    // Given
    std::istringstream input("23|43^54&32; x");
    std::cin.rdbuf(input.rdbuf());
    double expected{31.0};

    // When
    double given{calculator::calculate()};

    // Then
    ASSERT_NEAR(given, expected, 0.00001);
}

TEST(CorrectCalculationBitwiseXORTest, ShouldReturnExpectedBitwiseXORResult_3) {
    // Given
    std::istringstream input("43^54&32; x");
    std::cin.rdbuf(input.rdbuf());
    double expected{11.0};

    // When
    double given{calculator::calculate()};

    // Then
    ASSERT_NEAR(given, expected, 0.00001);
}

TEST(CorrectCalculationBitwiseXORTest, ShouldReturnExpectedBitwiseXORResult_4) {
    // Given
    std::istringstream input("231.5|43^54&32; x");
    std::cin.rdbuf(input.rdbuf());
    double expected{239.0};

    // When
    double given{calculator::calculate()};

    // Then
    ASSERT_NEAR(given, expected, 0.00001);
}

TEST(CorrectCalculationBitwiseXORTest, ShouldReturnExpectedBitwiseXORResult_5) {
    // Given
    std::istringstream input("(231|43)^54&32; x");
    std::cin.rdbuf(input.rdbuf());
    double expected{207.0};

    // When
    double given{calculator::calculate()};

    // Then
    ASSERT_NEAR(given, expected, 0.00001);
}

TEST(CorrectCalculationBitwiseXORTest, ShouldReturnExpectedBitwiseXORResult_6) {
    // Given
    std::istringstream input("((231|43)^54)&32; x");
    std::cin.rdbuf(input.rdbuf());
    double expected{0.0};

    // When
    double given{calculator::calculate()};

    // Then
    ASSERT_NEAR(given, expected, 0.00001);
}

TEST(CorrectCalculationBitwiseXORTest, ShouldReturnExpectedBitwiseXORResult_7) {
    // Given
    std::istringstream input("2*3|2^34; x");
    std::cin.rdbuf(input.rdbuf());
    double expected{38.0};

    // When
    double given{calculator::calculate()};

    // Then
    ASSERT_NEAR(given, expected, 0.00001);
}

TEST(CorrectCalculationBitwiseXORTest, ShouldReturnExpectedBitwiseXORResult_8) {
    // Given
    std::istringstream input("3|32^3&731|13; x");
    std::cin.rdbuf(input.rdbuf());
    double expected{47.0};

    // When
    double given{calculator::calculate()};

    // Then
    ASSERT_NEAR(given, expected, 0.00001);
}
////////////////////////////////////////////////////////////////////////////////
TEST(CorrectCalculationBitwiseORTest, ShouldReturnExpectedBitwiseORResult_1) {
    // Given
    std::istringstream input("23|43; x");
    std::cin.rdbuf(input.rdbuf());
    double expected{63.0};

    // When
    double given{calculator::calculate()};

    // Then
    ASSERT_NEAR(given, expected, 0.00001);
}

TEST(CorrectCalculationBitwiseORTest, ShouldReturnExpectedBitwiseORResult_2) {
    // Given
    std::istringstream input("23|43|54; x");
    std::cin.rdbuf(input.rdbuf());
    double expected{63.0};

    // When
    double given{calculator::calculate()};

    // Then
    ASSERT_NEAR(given, expected, 0.00001);
}

TEST(CorrectCalculationBitwiseORTest, ShouldReturnExpectedBitwiseORResult_3) {
    // Given
    std::istringstream input("(23|43)|54; x");
    std::cin.rdbuf(input.rdbuf());
    double expected{63.0};

    // When
    double given{calculator::calculate()};

    // Then
    ASSERT_NEAR(given, expected, 0.00001);
}

TEST(CorrectCalculationBitwiseORTest, ShouldReturnExpectedBitwiseORResult_4) {
    // Given
    std::istringstream input("2|5!; x");
    std::cin.rdbuf(input.rdbuf());
    double expected{122.0};

    // When
    double given{calculator::calculate()};

    // Then
    ASSERT_NEAR(given, expected, 0.00001);
}

TEST(CorrectCalculationBitwiseORTest, ShouldReturnExpectedBitwiseORResult_5) {
    // Given
    std::istringstream input("(2|5)!; x");
    std::cin.rdbuf(input.rdbuf());
    double expected{5040.0};

    // When
    double given{calculator::calculate()};

    // Then
    ASSERT_NEAR(given, expected, 0.00001);
}

TEST(CorrectCalculationBitwiseORTest, ShouldReturnExpectedBitwiseORResult_6) {
    // Given
    std::istringstream input("(!2|5)!; x");
    std::cin.rdbuf(input.rdbuf());
    double expected{120.0};

    // When
    double given{calculator::calculate()};

    // Then
    ASSERT_NEAR(given, expected, 0.00001);
}
////////////////////////////////////////////////////////////////////////////////

}  // namespace
