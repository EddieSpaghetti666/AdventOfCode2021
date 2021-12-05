#include "day5.h"

#include <cassert>
#include <cmath>
#include <regex>

#include "../common.h"

void fillLine(std::vector<std::vector<int>>& floorMap, const Point& a,
              const Point& b) {
  Point start = a;
  Point end = b;
  do {
    floorMap[start.y][start.x] += 1;

    //Move the start point closer to end point
    if (start.x != end.x) start.x = start.x < end.x ? start.x + 1 : start.x - 1;
    if (start.y != end.y) start.y = start.y < end.y ? start.y + 1 : start.y - 1;
  } while (start.x != end.x || start.y != end.y);
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

std::pair<Point, Point> getPoints(const std::string& line) {
  const auto regex = std::regex("(?:^(\\d+),(\\d+) -> (\\d+),(\\d+)$)");
  auto matchResults = std::smatch();
  std::regex_search(line, matchResults, regex);
  assert(matchResults.size() == 5);  // 1 for overall match 4 for each x/y coord

  Point a, b;
  a = {stoi(matchResults[1]), stoi(matchResults[2])};
  b = {stoi(matchResults[3]), stoi(matchResults[4])};
  return std::make_pair(a, b);
}

int mostDangerousAreas(const std::string& fileName) {
  const auto lineSegments = parseInputToVector<std::string>(fileName);

  std::vector<std::vector<int>> floorMap(1000, std::vector<int>(1000));

  for (const auto& line : lineSegments) {
    const auto points = getPoints(line);
    fillLine(floorMap, points.first, points.second);
  }

  return countDangerousAreas(floorMap);
}
