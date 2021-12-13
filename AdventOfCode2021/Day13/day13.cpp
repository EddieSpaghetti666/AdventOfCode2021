#include "day13.h"

#include <cassert>
#include <regex>
#include <set>
#include <utility>

#include "../common.h"

using isVertical = bool;
using Point = std::pair<int, int>;
using Fold = std::pair<isVertical, int>;

std::set<Point> getPoints(const std::vector<std::string>& paper) {
  std::set<Point> points;
  auto regex = std::regex("(\\d+),(\\d+)");
  auto matchResults = std::smatch();
  for (auto line : paper) {
    std::regex_search(line, matchResults, regex);
    if (matchResults.size() != 3)
      break;  // You got to the fold instructions.
    else {
      assert(matchResults.size() ==
             3);  // 1 for overall match 2 for the x,y coords of the point.
      auto x = stoi(matchResults[1]);
      auto y = stoi(matchResults[2]);
      points.insert(std::make_pair(x, y));
    }
  }
  return points;
}

std::vector<Fold> getFolds(const std::vector<std::string>& paper) {
  std::vector<Fold> folds;
  auto regex = std::regex("fold along (x|y)=(\\d+)");
  auto matchResults = std::smatch();
  for (auto line : paper) {
    std::regex_search(line, matchResults, regex);
    if (matchResults.empty()) continue;
    assert(matchResults.size() ==
           3);  // 1 for overall match, 1 for x/y and 1 for the fold line #
    bool isVertical = matchResults[1] == 'x';
    auto foldLocation = stoi(matchResults[2]);
    folds.push_back(std::make_pair(isVertical, foldLocation));
  }
  return folds;
}

std::set<Point> foldPaper(std::set<Point> points,
                          const std::vector<Fold>& folds) {
  int foldLine;
  bool isVert;
  std::function<Point(const Point&)> foldPoint;

  auto horizontalFoldPoint = [&foldLine](const Point& point) -> Point {
    auto distanceFromFold = point.second - foldLine;
    if (distanceFromFold < 0)
      return point;
    else
      return {point.first, foldLine - distanceFromFold};
  };

  auto verticalFoldPoint = [&foldLine](const Point& point) -> Point {
    auto distanceFromFold = point.first - foldLine;
    if (distanceFromFold < 0)
      return point;
    else
      return {foldLine - distanceFromFold, point.second};
  };

  for (auto fold : folds) {
    std::set<Point> pointsAfterFold;
    isVert = fold.first;
    foldLine = fold.second;
    if (isVert)
      foldPoint = verticalFoldPoint;
    else
      foldPoint = horizontalFoldPoint;
    std::transform(points.cbegin(), points.cend(),
                   std::inserter(pointsAfterFold, pointsAfterFold.begin()),
                   foldPoint);
    points = pointsAfterFold;
  }

  return points;
}

int pointsAfter1Fold(const std::string& fileName) {
  const auto paper = parseInputToVector<std::string>(fileName);
  auto points = getPoints(paper);
  auto folds = getFolds(paper);
  auto pointsAfterFold = foldPaper(points, {folds[0]});

  return pointsAfterFold.size();
}

std::pair<size_t, size_t> rowsAndCols(const std::set<Point>& points) {
  auto highestCol = std::max_element(points.cbegin(), points.cend(),
                                     [](auto point1, auto point2) {
                                       return point1.first < point2.first;
                                     })
                        ->first;
  auto highestRow = std::max_element(points.cbegin(), points.cend(),
                                     [](auto point1, auto point2) {
                                       return point1.second < point2.second;
                                     })
                        ->second;
  return std::make_pair(highestRow, highestCol);
}

void printCode(const std::vector<std::vector<char>>& code) {
  for (auto row : code) {
    for (const auto c : row) {
      std::cout << c;
    }
    std::cout << std::endl;
  }
}
void pointsAfterEveryFold(const std::string& fileName) {
  const auto paper = parseInputToVector<std::string>(fileName);
  auto points = getPoints(paper);
  auto folds = getFolds(paper);

  auto pointsAfterFold = foldPaper(points, folds);

  auto [rows, cols] = rowsAndCols(pointsAfterFold);
  std::vector<std::vector<char>> code(
      static_cast<size_t>(rows + 1),
      std::vector<char>(static_cast<size_t>(cols + 1), '.'));

  for (auto point : pointsAfterFold) {
    auto [col, row] = point;
    code[row][col] = '#';
  }

  printCode(code);
}
