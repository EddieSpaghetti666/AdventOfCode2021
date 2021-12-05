#include "day4.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>

std::deque<int> getBingoNumbers(const std::string& filename) {
  std::deque<int> bingoNumbers;
  std::fstream file(filename);
  int bingoNum;
  while (file >> bingoNum) {
    bingoNumbers.push_back(bingoNum);
    if (file.peek() == ',')
      file.get();
    else if (file.peek() == '\n')
      break;
  }
  return bingoNumbers;
}

std::vector<BingoBoard> getBingoBoards(const std::string& fileName) {
  std::vector<BingoBoard> boards;
  std::vector<std::vector<Square>> currentBoard;

  std::vector<Square> currentRow;
  std::fstream file(fileName);
  file.ignore(1000, '\n');  // ignore the first line of numbers

  int number;
  while (file >> std::skipws >> number) {
    currentRow.push_back({number});
    if (file.peek() == '\n') {
      currentBoard.push_back(currentRow);
      currentRow.clear();
      if (currentBoard.size() >= 5) {
        boards.push_back({currentBoard});
        currentBoard.clear();
      }
    }
  }

  currentBoard.push_back(currentRow);
  boards.push_back({currentBoard});

  return boards;
}

void checkRow(BingoBoard& board, const int row) {
  int matchedNumbers =
      std::count_if(board.board[row].begin(), board.board[row].end(),
                    [](Square square) { return square.marked; });
  if (matchedNumbers > board.mostInARow) board.mostInARow = matchedNumbers;
}

void checkCol(BingoBoard& board, const int col) {
  int matchedNumbers = 0;
  for (int i = 0; i < board.board.size(); ++i) {
    if (board.board[i][col].marked) matchedNumbers++;
  }
  if (matchedNumbers > board.mostInARow) board.mostInARow = matchedNumbers;
}

void drawNumber(std::vector<int>& calledNumbers, std::deque<int>& numbers,
                std::vector<BingoBoard>& boards) {
  int calledNumber = numbers[0];
  numbers.pop_front();
  for (auto& board : boards) {
    for (int row = 0; row < board.board.size(); ++row) {
      for (int col = 0; col < board.board.size(); ++col) {
        if (board.board[row][col].num == calledNumber) {
          board.board[row][col].marked = true;
          checkRow(board, row);
          checkCol(board, col);
        }
      }
    }
  }
  calledNumbers.push_back(calledNumber);
}

int unmarkedNumbers(const BingoBoard& winningBoard) {
  int total = 0;
  for (const auto& row : winningBoard.board) {
    int rowTotal = 0;
    for (const auto& square : row) {
      if (!square.marked) rowTotal += square.num;
    }
    total += rowTotal;
  }
  return total;
}

int boardNumbers(const std::string& fileName, bool losingBoard = false) {
  auto uncalledNumbers = getBingoNumbers(fileName);
  auto boards = getBingoBoards(fileName);
  std::vector<int> calledNumbers;
  while (boards[0].mostInARow < 5) {
    drawNumber(calledNumbers, uncalledNumbers, boards);
    std::sort(boards.begin(), boards.end(),
              [losingBoard](BingoBoard a, BingoBoard b) {
                return losingBoard ? a.mostInARow < b.mostInARow
                                   : a.mostInARow > b.mostInARow;
              });
  }
  int lastDrawnNumber = calledNumbers.back();
  int unmarkedTotal = unmarkedNumbers(boards[0]);

  return lastDrawnNumber * unmarkedTotal;
}
int winningBoardNumbers(const std::string& fileName) {
  return boardNumbers(fileName);
}

int losingBoardNumbers(const std::string& fileName) {
  return boardNumbers(fileName, true);
}
