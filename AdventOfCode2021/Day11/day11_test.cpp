#include "day11.h"

#include <gtest/gtest.h>

#include "../common.h"

const std::string inputData = "Day11\\input.txt";

const std::string testInput = "Day11\\test_input.txt";

TEST(Day11, testInput) { ASSERT_EQ(1656, totalFlashes(testInput)); }

TEST(Day11, realInput) { std::cout << totalFlashes(inputData) << std::endl; }

TEST(Day11, secondTestInput) { ASSERT_EQ(195, firstSync(testInput)); }

TEST(Day11, secondRealInput) { std::cout << firstSync(inputData) << std::endl; }
