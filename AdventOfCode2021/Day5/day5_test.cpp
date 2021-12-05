#include <gtest/gtest.h>

#include "../common.h"
#include "day5.h"

const std::string inputData = "Day5\\input.txt";
const std::string testInput = "Day5\\test_input.txt";

TEST(Day5, testInput) {
  ASSERT_EQ(12, mostDangerousAreas(testInput));
}

TEST(Day5, realInput) {
  std::cout << mostDangerousAreas(inputData) << std::endl;
}

//TEST(Day5, secondTestInput) { /* Test 2 here */ }

//TEST(Day5, aimRealInput) {
//}
