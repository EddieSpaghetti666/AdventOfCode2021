#include "day4.h"

#include <gtest/gtest.h>

#include "../common.h"

const std::string inputData = "Day4\\input.txt";

class Day4 : public ::testing::Test {
 protected:
  void SetUp() override { testData = {/* Test data here */}; };
  std::vector<std::string> testData;
};

TEST_F(Day4, testInput) {
  ASSERT_EQ(4512, winningBoardNumbers("Day4\\test_input.txt"));
}

TEST_F(Day4, realInput) {
  std::cout << winningBoardNumbers(inputData) << std::endl;
}

TEST_F(Day4, secondTestInput) {
  ASSERT_EQ(1924, losingBoardNumbers("Day4\\test_input.txt"));
}

TEST_F(Day4, secondTestRealInput) {
  std::cout << losingBoardNumbers(inputData) << std::endl;
}

