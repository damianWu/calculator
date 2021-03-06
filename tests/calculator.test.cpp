// Copyright [2022] <@damianWu>
#include "calculator/calculator.hpp"

#include <gtest/gtest.h>

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
                         ::testing::Values("2+2; @", "2*2; @", "4; @",
                                           "20/5; @"));
// ////////////////////////////////////////////////////////////////////////////////
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
                         ::testing::Values("{(4+5)*6}/(3+4); @",
                                           "({4+5}*6)/(3+4); @",
                                           "({4+5}*6)/{3+4}; @"));
////////////////////////////////////////////////////////////////////////////////
TEST(CorrectCalculationTest, ShouldReturnExpectedResult_1) {
    // Given
    std::istringstream input("1-2-3; @");
    std::cin.rdbuf(input.rdbuf());
    double expected{-4.0};

    // When
    double given{calculator::calculate()};

    // Then
    ASSERT_NEAR(given, expected, 0.00001);
}

TEST(CorrectCalculationTest, ShouldReturnExpectedResult_2) {
    // Given
    std::istringstream input("280; @");
    std::cin.rdbuf(input.rdbuf());
    double expected{280.0};

    // When
    double given{calculator::calculate()};

    // Then
    ASSERT_NEAR(given, expected, 0.00001);
}

TEST(CorrectCalculationTest, ShouldReturnExpectedResult_3) {
    // Given
    std::istringstream input("3!*2*2; @");
    std::cin.rdbuf(input.rdbuf());
    double expected{24.0};

    // When
    double given{calculator::calculate()};

    // Then
    ASSERT_NEAR(given, expected, 0.00001);
}

TEST(CorrectCalculationTest, ShouldReturnExpectedResult_4) {
    // Given
    std::istringstream input("2*2+8/4%3; @");
    std::cin.rdbuf(input.rdbuf());
    double expected{6.0};

    // When
    double given{calculator::calculate()};

    // Then
    ASSERT_NEAR(given, expected, 0.00001);
}

TEST(CorrectCalculationTest, ShouldReturnExpectedResult_5) {
    // Given
    std::istringstream input("2*2+8/4%3-30^3; @");
    std::cin.rdbuf(input.rdbuf());
    double expected{-21.0};

    // When
    double given{calculator::calculate()};

    // Then
    ASSERT_NEAR(given, expected, 0.00001);
}

TEST(CorrectCalculationTest, ShouldReturnExpectedResult_6) {
    // Given
    std::istringstream input("-30^3; @");
    std::cin.rdbuf(input.rdbuf());
    double expected{-31.0};

    // When
    double given{calculator::calculate()};

    // Then
    ASSERT_NEAR(given, expected, 0.00001);
}

TEST(CorrectCalculationTest, ShouldReturnExpectedResult_7) {
    // Given
    std::istringstream input("-(30^3); @");
    std::cin.rdbuf(input.rdbuf());
    double expected{-29.0};

    // When
    double given{calculator::calculate()};

    // Then
    ASSERT_NEAR(given, expected, 0.00001);
}

TEST(CorrectCalculationTest, ShouldReturnExpectedResult_8) {
    // Given
    std::istringstream input("!4!-1; @");
    std::cin.rdbuf(input.rdbuf());
    double expected{-1.0};

    // When
    double given{calculator::calculate()};

    // Then
    ASSERT_NEAR(given, expected, 0.00001);
}

TEST(CorrectCalculationTest, ShouldReturnExpectedResult_9) {
    // Given
    std::istringstream input("10-10*10+10; @");
    std::cin.rdbuf(input.rdbuf());
    double expected{-80.0};

    // When
    double given{calculator::calculate()};

    // Then
    ASSERT_NEAR(given, expected, 0.00001);
}
////////////////////////////////////////////////////////////////////////////////
TEST(CorrectCalculationFactorialTest, ShouldReturnExpectedFactorialResult_1) {
    // Given
    std::istringstream input("0!; @");
    std::cin.rdbuf(input.rdbuf());
    double expected{1.0};

    // When
    double given{calculator::calculate()};

    // Then
    ASSERT_NEAR(given, expected, 0.00001);
}

TEST(CorrectCalculationFactorialTest, ShouldReturnExpectedFactorialResult_2) {
    // Given
    std::istringstream input("4!; @");
    std::cin.rdbuf(input.rdbuf());
    double expected{24.0};

    // When
    double given{calculator::calculate()};

    // Then
    ASSERT_NEAR(given, expected, 0.00001);
}

TEST(CorrectCalculationFactorialTest, ShouldReturnExpectedFactorialResult_3) {
    // Given
    std::istringstream input("8!; @");
    std::cin.rdbuf(input.rdbuf());
    double expected{40320.0};

    // When
    double given{calculator::calculate()};

    // Then
    ASSERT_NEAR(given, expected, 0.00001);
}

TEST(CorrectCalculationFactorialTest, ShouldReturnExpectedFactorialResult_4) {
    // Given
    std::istringstream input("2*3!; @");
    std::cin.rdbuf(input.rdbuf());
    double expected{12.0};

    // When
    double given{calculator::calculate()};

    // Then
    ASSERT_NEAR(given, expected, 0.00001);
}

TEST(CorrectCalculationFactorialTest, ShouldReturnExpectedFactorialResult_5) {
    // Given
    std::istringstream input("2*(3!); @");
    std::cin.rdbuf(input.rdbuf());
    double expected{12.0};

    // When
    double given{calculator::calculate()};

    // Then
    ASSERT_NEAR(given, expected, 0.00001);
}

TEST(CorrectCalculationFactorialTest, ShouldReturnExpectedFactorialResult_6) {
    // Given
    std::istringstream input("(2*3)!; @");
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
    std::istringstream input("!(324); @");
    std::cin.rdbuf(input.rdbuf());
    double expected{0.0};

    // When
    double given{calculator::calculate()};

    // Then
    ASSERT_NEAR(given, expected, 0.00001);
}

TEST(CorrectCalculationBinaryNotTest, ShouldReturnExpectedBinaryNotResult_2) {
    // Given
    std::istringstream input("2*!(34); @");
    std::cin.rdbuf(input.rdbuf());
    double expected{0.0};

    // When
    double given{calculator::calculate()};

    // Then
    ASSERT_NEAR(given, expected, 0.00001);
}

TEST(CorrectCalculationBinaryNotTest, ShouldReturnExpectedBinaryNotResult_3) {
    // Given
    std::istringstream input("!(0); @");
    std::cin.rdbuf(input.rdbuf());
    double expected{1.0};

    // When
    double given{calculator::calculate()};

    // Then
    ASSERT_NEAR(given, expected, 0.00001);
}

TEST(CorrectCalculationBinaryNotTest, ShouldReturnExpectedBinaryNotResult_4) {
    // Given
    std::istringstream input("!(0)+1; @");
    std::cin.rdbuf(input.rdbuf());
    double expected{2.0};

    // When
    double given{calculator::calculate()};

    // Then
    ASSERT_NEAR(given, expected, 0.00001);
}

TEST(CorrectCalculationBinaryNotTest, ShouldReturnExpectedBinaryNotResult_5) {
    // Given
    std::istringstream input("!2+3; @");
    std::cin.rdbuf(input.rdbuf());
    double expected{3.0};

    // When
    double given{calculator::calculate()};

    // Then
    ASSERT_NEAR(given, expected, 0.00001);
}

TEST(CorrectCalculationBinaryNotTest, ShouldReturnExpectedBinaryNotResult_6) {
    // Given
    std::istringstream input("(!3)!; @");
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
    std::istringstream input("(23^4)^54; @");
    std::cin.rdbuf(input.rdbuf());
    double expected{37.0};

    // When
    double given{calculator::calculate()};

    // Then
    ASSERT_NEAR(given, expected, 0.00001);
}

TEST(CorrectCalculationBitwiseXORTest, ShouldReturnExpectedBitwiseXORResult_2) {
    // Given
    std::istringstream input("23|43^54&32; @");
    std::cin.rdbuf(input.rdbuf());
    double expected{31.0};

    // When
    double given{calculator::calculate()};

    // Then
    ASSERT_NEAR(given, expected, 0.00001);
}

TEST(CorrectCalculationBitwiseXORTest, ShouldReturnExpectedBitwiseXORResult_3) {
    // Given
    std::istringstream input("43^54&32; @");
    std::cin.rdbuf(input.rdbuf());
    double expected{11.0};

    // When
    double given{calculator::calculate()};

    // Then
    ASSERT_NEAR(given, expected, 0.00001);
}

TEST(CorrectCalculationBitwiseXORTest, ShouldReturnExpectedBitwiseXORResult_4) {
    // Given
    std::istringstream input("231.5|43^54&32; @");
    std::cin.rdbuf(input.rdbuf());
    double expected{239.0};

    // When
    double given{calculator::calculate()};

    // Then
    ASSERT_NEAR(given, expected, 0.00001);
}

TEST(CorrectCalculationBitwiseXORTest, ShouldReturnExpectedBitwiseXORResult_5) {
    // Given
    std::istringstream input("(231|43)^54&32; @");
    std::cin.rdbuf(input.rdbuf());
    double expected{207.0};

    // When
    double given{calculator::calculate()};

    // Then
    ASSERT_NEAR(given, expected, 0.00001);
}

TEST(CorrectCalculationBitwiseXORTest, ShouldReturnExpectedBitwiseXORResult_6) {
    // Given
    std::istringstream input("((231|43)^54)&32; @");
    std::cin.rdbuf(input.rdbuf());
    double expected{0.0};

    // When
    double given{calculator::calculate()};

    // Then
    ASSERT_NEAR(given, expected, 0.00001);
}

TEST(CorrectCalculationBitwiseXORTest, ShouldReturnExpectedBitwiseXORResult_7) {
    // Given
    std::istringstream input("2*3|2^34; @");
    std::cin.rdbuf(input.rdbuf());
    double expected{38.0};

    // When
    double given{calculator::calculate()};

    // Then
    ASSERT_NEAR(given, expected, 0.00001);
}

TEST(CorrectCalculationBitwiseXORTest, ShouldReturnExpectedBitwiseXORResult_8) {
    // Given
    std::istringstream input("3|32^3&731|13; @");
    std::cin.rdbuf(input.rdbuf());
    double expected{47.0};

    // When
    double given{calculator::calculate()};

    // Then
    ASSERT_NEAR(given, expected, 0.00001);
}

TEST(CorrectCalculationBitwiseXORTest, ShouldReturnExpectedBitwiseXORResult_9) {
    // Given
    std::istringstream input("23|43-1^54&32; @");
    std::cin.rdbuf(input.rdbuf());
    double expected{31.0};

    // When
    double given{calculator::calculate()};

    // Then
    ASSERT_NEAR(given, expected, 0.00001);
}
////////////////////////////////////////////////////////////////////////////////
TEST(CorrectCalculationBitwiseORTest, ShouldReturnExpectedBitwiseORResult_1) {
    // Given
    std::istringstream input("23|43; @");
    std::cin.rdbuf(input.rdbuf());
    double expected{63.0};

    // When
    double given{calculator::calculate()};

    // Then
    ASSERT_NEAR(given, expected, 0.00001);
}

TEST(CorrectCalculationBitwiseORTest, ShouldReturnExpectedBitwiseORResult_2) {
    // Given
    std::istringstream input("23|43|54; @");
    std::cin.rdbuf(input.rdbuf());
    double expected{63.0};

    // When
    double given{calculator::calculate()};

    // Then
    ASSERT_NEAR(given, expected, 0.00001);
}

TEST(CorrectCalculationBitwiseORTest, ShouldReturnExpectedBitwiseORResult_3) {
    // Given
    std::istringstream input("(23|43)|54; @");
    std::cin.rdbuf(input.rdbuf());
    double expected{63.0};

    // When
    double given{calculator::calculate()};

    // Then
    ASSERT_NEAR(given, expected, 0.00001);
}

TEST(CorrectCalculationBitwiseORTest, ShouldReturnExpectedBitwiseORResult_4) {
    // Given
    std::istringstream input("2|5!; @");
    std::cin.rdbuf(input.rdbuf());
    double expected{122.0};

    // When
    double given{calculator::calculate()};

    // Then
    ASSERT_NEAR(given, expected, 0.00001);
}

TEST(CorrectCalculationBitwiseORTest, ShouldReturnExpectedBitwiseORResult_5) {
    // Given
    std::istringstream input("(2|5)!; @");
    std::cin.rdbuf(input.rdbuf());
    double expected{5040.0};

    // When
    double given{calculator::calculate()};

    // Then
    ASSERT_NEAR(given, expected, 0.00001);
}

TEST(CorrectCalculationBitwiseORTest, ShouldReturnExpectedBitwiseORResult_6) {
    // Given
    std::istringstream input("(!2|5)!; @");
    std::cin.rdbuf(input.rdbuf());
    double expected{120.0};

    // When
    double given{calculator::calculate()};

    // Then
    ASSERT_NEAR(given, expected, 0.00001);
}
////////////////////////////////////////////////////////////////////////////////
TEST(CorrectCalculationNegativeNumbers, ShouldReturnExpectedNegativeResult_1) {
    // Given
    std::istringstream input("-1/2; @");
    std::cin.rdbuf(input.rdbuf());
    double expected{-0.5};

    // When
    double given{calculator::calculate()};

    // Then
    ASSERT_NEAR(given, expected, 0.00001);
}
////////////////////////////////////////////////////////////////////////////////
TEST(CorrectCalculationModuloOperator, ShouldReturnExpectedModuloResult_1) {
    // Given
    std::istringstream input("4%2; @");
    std::cin.rdbuf(input.rdbuf());
    double expected{0.0};

    // When
    double given{calculator::calculate()};

    // Then
    ASSERT_NEAR(given, expected, 0.00001);
}

TEST(CorrectCalculationModuloOperator, ShouldReturnExpectedModuloResult_2) {
    // Given
    std::istringstream input("2%2; @");
    std::cin.rdbuf(input.rdbuf());
    double expected{0.0};

    // When
    double given{calculator::calculate()};

    // Then
    ASSERT_NEAR(given, expected, 0.00001);
}

TEST(CorrectCalculationModuloOperator, ShouldReturnExpectedModuloResult_3) {
    // Given
    std::istringstream input("2%3; @");
    std::cin.rdbuf(input.rdbuf());
    double expected{2.0};

    // When
    double given{calculator::calculate()};

    // Then
    ASSERT_NEAR(given, expected, 0.00001);
}

TEST(CorrectCalculationModuloOperator, ShouldReturnExpectedModuloResult_4) {
    // Given
    std::istringstream input("5%3; @");
    std::cin.rdbuf(input.rdbuf());
    double expected{2.0};

    // When
    double given{calculator::calculate()};

    // Then
    ASSERT_NEAR(given, expected, 0.00001);
}

TEST(CorrectCalculationModuloOperator, ShouldReturnExpectedModuloResult_5) {
    // Given
    std::istringstream input("3%2; @");
    std::cin.rdbuf(input.rdbuf());
    double expected{1.0};

    // When
    double given{calculator::calculate()};

    // Then
    ASSERT_NEAR(given, expected, 0.00001);
}

TEST(CorrectCalculationModuloOperator, ShouldReturnExpectedModuloResult_6) {
    // Given
    std::istringstream input("6.7%3.3; @");
    std::cin.rdbuf(input.rdbuf());
    double expected{0.1};

    // When
    double given{calculator::calculate()};

    // Then
    ASSERT_NEAR(given, expected, 0.00001);
}
////////////////////////////////////////////////////////////////////////////////
TEST(CorrectCalculationBitwiseNotOperator,
     ShouldReturnExpectedBitwiseNotResult_1) {
    // Given
    std::istringstream input("~2; @");
    std::cin.rdbuf(input.rdbuf());
    double expected{-3.0};

    // When
    double given{calculator::calculate()};

    // Then
    ASSERT_NEAR(given, expected, 0.00001);
}
////////////////////////////////////////////////////////////////////////////////
}  // namespace
