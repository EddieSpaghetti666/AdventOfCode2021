#include "day13.h"

#include <gtest/gtest.h>

#include "../common.h"

const std::string inputData = "Day13\\input.txt";

const std::string testInput = "Day13\\test_input.txt";

TEST(Day13, testInput) { ASSERT_EQ(17, pointsAfter1Fold(testInput)); }

TEST(Day13, realInput) {
  std::cout << pointsAfter1Fold(inputData) << std::endl;
}

TEST(Day13, secondTestInput) { pointsAfterEveryFold(testInput); }

TEST(Day13, secondRealInput) { pointsAfterEveryFold(inputData); }
