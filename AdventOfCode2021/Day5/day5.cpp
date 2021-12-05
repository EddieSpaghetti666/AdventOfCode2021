#include "day5.h"

#include <cassert>
#include <cmath>
#include <regex>

#include "../common.h"

void fillVerticalLine(std::vector<std::vector<int>>& floorMap, const Point& a,
                      const Point& b) {
  assert(a.x == b.x);
  int startY = std::min(a.y, b.y);
  int endY = std::max(a.y, b.y);
  for (; startY <= endY; ++startY) {
    floorMap[startY][a.x] += 1;
  }
}

void fillHorizontalLine(std::vector<std::vector<int>>& floorMap, const Point& a,
                        const Point& b) {
  assert(a.y == b.y);
  int startX = std::min(a.x, b.x);
  int endX = std::max(a.x, b.x);
  for (; startX <= endX; ++startX) {
    floorMap[a.y][startX] += 1;
  }
}
void fillDiagonalLine(std::vector<std::vector<int>>& floorMap, const Point& a,
                      const Point& b) {
  assert(std::abs(a.y - b.y) == std::abs(a.x - b.x));
  Point start = a;
  Point end = b;
  do {
    floorMap[start.y][start.x] += 1;
    if (start.x < end.x)
      start.x++;
    else
      start.x--;
    if (start.y < end.y)
      start.y++;
    else
      start.y--;
  } while (start.x != end.x && start.y != end.y);
  floorMap[end.y][end.x] += 1;
}
int countDangerousAreas(std::vector<std::vector<int>>& floorMap) {
  int dangerousAreas = 0;
  for (const auto& row : floorMap) {
    int rowTotal =
        std::count_if(row.begin(), row.end(), [](int num) { return num >= 2; });
    dangerousAreas += rowTotal;
  }
  return dangerousAreas;
}
int mostDangerousAreas(const std::string& fileName) {
  const auto lineSegments = parseInputToVector<std::string>(fileName);

  std::vector<std::vector<int>> floorMap(1000, std::vector<int>(1000));
  Point a, b;
  const auto regex = std::regex("(?:^(\\d+),(\\d+) -> (\\d+),(\\d+)$)");
  for (const auto& line : lineSegments) {
    auto matchResults = std::smatch();
    if (!std::regex_search(line, matchResults, regex)) return -1;

    assert(matchResults.size() == 5); //1 for overall match 4 for each x/y coord
    
    a = {stoi(matchResults[1]), stoi(matchResults[2])};
    
    b = {stoi(matchResults[3]), stoi(matchResults[4])};
    if (a.x == b.x)
      fillVerticalLine(floorMap, a, b);
    else if (a.y == b.y)
      fillHorizontalLine(floorMap, a, b);
    else if (std::abs(a.y - b.y) == std::abs(a.x - b.x)) //Lines are 45 degrees so slope == 1
      fillDiagonalLine(floorMap, a, b);
  }

  int dangerousAreaCount = countDangerousAreas(floorMap);
  return dangerousAreaCount;
}
