#include "day3.h"

#include <gtest/gtest.h>

#include "../common.h"

const std::string inputData = "Day3\\input.txt";

class Day3 : public ::testing::Test {
 protected:
  void SetUp() override {
    testData = {"00100", "11110", "10110", "10111", "10101", "01111",
                "00111", "11100", "10000", "11001", "00010", "01010"};
  };
  std::vector<std::string> testData;
};

TEST_F(Day3, testInput) { ASSERT_EQ(198, binaryDiagnostic(testData)); }

TEST_F(Day3, realInput) {
  std::cout << answerFromFileInput<std::string>(inputData, binaryDiagnostic)
            << std::endl;
}

TEST_F(Day3, secondTestInput) { ASSERT_EQ(230, lifeSupportRating(testData)); }

TEST_F(Day3, aimRealInput) {
  std::cout << answerFromFileInput<std::string>(inputData, lifeSupportRating)
            << std::endl;
}
