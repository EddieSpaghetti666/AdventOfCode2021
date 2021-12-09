#include "day9.h"

#include <gtest/gtest.h>

#include "../common.h"

const std::string inputData = "Day9\\input.txt";

const std::string testInput = "Day9\\test_input.txt";

TEST(Day9, testInput) { ASSERT_EQ(15, riskLevel(testInput)); }

TEST(Day9, realInput) { std::cout << riskLevel(inputData) << std::endl; }

TEST(Day9, secondTestInput) { ASSERT_EQ(1134, basins(testInput)); }

TEST(Day9, secondRealInput) { std::cout << basins(inputData) << std::endl; }
