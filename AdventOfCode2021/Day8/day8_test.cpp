#include "day8.h"

#include <gtest/gtest.h>

#include "../common.h"

const std::string inputData = "Day8\\input.txt";

const std::string testInput = "Day8\\test_input.txt";

TEST(Day8, testInput) { ASSERT_EQ(26, frequencyOfDigits(testInput)); }

TEST(Day8, realInput) {
  std::cout << frequencyOfDigits(inputData) << std::endl;
}

TEST(Day8, secondTestInput) { ASSERT_EQ(61229, totalDigitOutput(testInput)); }

TEST(Day8, secondRealInput) { std::cout << totalDigitOutput(inputData) << std::endl; }
