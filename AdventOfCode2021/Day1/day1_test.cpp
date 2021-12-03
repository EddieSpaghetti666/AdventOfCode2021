#include "day1.h"
#include "../common.h"

#include <gtest/gtest.h>
TEST(Sonarsweep, testInput) {
  std::vector<int> input = {199, 200, 208, 210, 200, 207, 240, 269, 260, 263};
  ASSERT_EQ(7, depthIncreases(input));
}

TEST(Sonarsweep, realInput) {
  std::cout << answerFromFileInput<int>("Day1\\day1Input.txt", depthIncreases) << std::endl;
}

TEST(Sonarsweep, windowTestInput) {
  std::vector<int> input = {199, 200, 208, 210, 200, 207, 240, 269, 260, 263};
	ASSERT_EQ(5, windowDepthIncreases(input));
}

TEST(Sonarsweep, windowRealInput){
	std::cout << answerFromFileInput<int>("Day1\\day1Input.txt", windowDepthIncreases) << std::endl;
}
