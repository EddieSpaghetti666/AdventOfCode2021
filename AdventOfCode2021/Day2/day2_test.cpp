#include "day2.h"

#include <gtest/gtest.h>

#include "../common.h"

const std::string inputData = "Day2\\input.txt";

class Day2 : public ::testing::Test {
 protected:
  void SetUp() override {
    testData = {"forward 5", "down 5", "forward 8",
                "up 3",      "down 8", "forward 2"};
  };
  std::vector<std::string> testData;
};

TEST_F(Day2, testInput) { ASSERT_EQ(150, submarinePosition(testData)); }

TEST(Submarine, realInput) {
  std::cout << answerFromFileInput<std::string>(inputData,
                                                     submarinePosition)
            << std::endl;
}

TEST_F(Day2, aimTestInput) { ASSERT_EQ(900, aimSubmarinePosition(testData)); }

TEST(Submarine, aimRealInput) {
  std::cout << answerFromFileInput<std::string>(inputData,
                                                     aimSubmarinePosition)
            << std::endl;
}
