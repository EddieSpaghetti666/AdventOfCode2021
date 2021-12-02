#include "day2.h"

#include <gtest/gtest.h>

#include "../common.h"
TEST(Submarine, testInput) {
  std::vector<std::string> directions = {"forward 5", "down 5", "forward 8",
                                         "up 3",      "down 8", "forward 2"};
  ASSERT_EQ(150, submarinePosition(directions));
}

TEST(Submarine, realInput) {
  std::cout << answerFromFileInput<std::string, int>("Day2\\day2Input.txt",
                                                     submarinePosition)
            << std::endl;
}

TEST(Submarine, aimTestInput) {
  std::vector<std::string> directions = {"forward 5", "down 5", "forward 8",
                                         "up 3",      "down 8", "forward 2"};
  ASSERT_EQ(900, aimSubmarinePosition(directions));
}
TEST(Submarine, aimRealInput) {
  std::cout << answerFromFileInput<std::string, int>("Day2\\day2Input.txt",
                                                     aimSubmarinePosition)
            << std::endl;
}
