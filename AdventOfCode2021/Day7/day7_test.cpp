#include "day7.h"

#include <gtest/gtest.h>

#include "../common.h"

const std::string inputData = "Day7\\input.txt";

const std::string testInput = "Day7\\test_input.txt";

TEST(Day7, testInput) { ASSERT_EQ(37, leastFuel(testInput)); }

TEST(Day7, realInput) { std::cout << leastFuel(inputData) << std::endl; }

TEST(Day7, secondTestInput) { ASSERT_EQ(168, leastFuel2(testInput)); }

TEST(Day7, aimRealInput) { std::cout << leastFuel2(inputData) << std::endl; }
