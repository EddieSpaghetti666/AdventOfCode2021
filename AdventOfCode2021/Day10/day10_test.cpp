#include "day10.h"

#include <gtest/gtest.h>

#include "../common.h"

const std::string inputData = "Day10\\input.txt";

const std::string testInput = "Day10\\test_input.txt";

TEST(Day10, testInput) { ASSERT_EQ(26397, syntaxScore(testInput)); }

TEST(Day10, realInput) { std::cout << syntaxScore(inputData) << std::endl; }

TEST(Day10, secondTestInput) {
  ASSERT_EQ(288957, autocompleteScore(testInput));
}

TEST(Day10, secondRealInput) {
  std::cout << autocompleteScore(inputData) << std::endl;
}
