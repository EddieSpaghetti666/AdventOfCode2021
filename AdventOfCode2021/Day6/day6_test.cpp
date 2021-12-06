#include "day6.h"

#include <gtest/gtest.h>

#include "../common.h"

const std::string inputData = "Day6\\input.txt";
const std::string testInput = "Day6\\test_input.txt";

TEST(Day6, testInput) { ASSERT_EQ(5934, totalLanternFish(testInput, 80)); }

TEST(Day6, realInput) {
  std::cout << totalLanternFish(inputData, 80) << std::endl;
}

TEST(Day6, secondTestInput) {
  ASSERT_EQ(26984457539, totalLanternFish(testInput, 256));
}

TEST(Day6, aimRealInput) {
  std::cout << totalLanternFish(inputData, 256) << std::endl;
}
