#pragma once
#include <vector>
#include <string>
#include <deque>
struct Square{
  int num;
  bool marked = false;
};

struct BingoBoard{
  std::vector<std::vector<Square>> board;
  int mostInARow = 0;
};


int winningBoardNumbers(const std::string& fileName);
int losingBoardNumbers(const std::string& fileName);
