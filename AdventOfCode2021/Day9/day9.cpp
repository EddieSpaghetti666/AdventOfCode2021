#include "day9.h"

#include <fstream>
#include <iostream>
#include <vector>

#include "../common.h"

std::vector<std::vector<int>> getHeightMap(const std::string& fileName) {
  std::vector<std::vector<int>> heightMap;
  std::vector<int> row;

  std::fstream file(fileName);
  std::string line;
  while (std::getline(file, line)) {
    std::transform(line.begin(), line.end(), std::back_inserter(row),
                   [](char c) { return c - '0'; });
    heightMap.push_back(row);
    row.clear();
  }

  return heightMap;
}
bool validCoords(const std::vector<std::vector<int>>& heightMap, const int i,
                 const int j) {
  return i >= 0 && i < heightMap.size() && j >= 0 && j < heightMap[i].size();
}
bool isLowPoint(const std::vector<std::vector<int>>& heightMap, const int i,
                const int j) {
  int currentDepth = heightMap[i][j];
  std::vector<std::pair<int, int>> adjacentCoords;
   for (auto offset : OFFSETS) {
    int k = i + offset.first;
    int l = j + offset.second;
    if (!validCoords(heightMap, k, l))
      continue;
    else if (heightMap[k][l] <= currentDepth)
      return false;
  }
  return true;
}
bool isLowPoint(const std::vector<std::vector<int>>& heightMap, std::vector<int>::iterator height){
}
std::vector<int> lowPoints(const std::vector<std::vector<int>>& heightMap) {
  std::vector<int> lowPoints;
  for (int i = 0; i < heightMap.size(); ++i) {
    for (int j = 0; j < heightMap[i].size(); ++j) {
      if (isLowPoint(heightMap, i, j)) lowPoints.push_back(heightMap[i][j]);
    }
  }
  return lowPoints;
}

int riskLevel(const std::string& fileName) {
  const auto heightMap = getHeightMap(fileName);
  const auto lp = lowPoints(heightMap);
  int riskLevel = 0;
  for (int lowPoint : lp) {
    riskLevel += lowPoint + 1;
  }
  return riskLevel;
}
void exploreBasin(const std::vector<std::vector<int>> heightMap,
                  std::vector<std::vector<bool>>& visited, int& size, int i,
                  int j) {
  for (auto offset : OFFSETS) {
    int k = i + offset.first;
    int l = j + offset.second;
    if (!validCoords(heightMap, k, l) || heightMap[k][l] == 9 || visited[k][l])
      continue;
    else {
      size++;
      visited[k][l] = true;
      exploreBasin(heightMap, visited, size, k, l);
    }
  }
}
std::vector<int> getBasinSizes(const std::vector<std::vector<int>>& heightMap) {
  std::vector<int> basins;
  std::vector<std::vector<bool>> visited(
      heightMap.size(), std::vector<bool>(heightMap[0].size(), false));
  for (int i = 0; i < heightMap.size(); ++i) {
    for (int j = 0; j < heightMap[i].size(); ++j) {
      if (heightMap[i][j] != 9 && !visited[i][j]) {
        int size = 0;
        exploreBasin(heightMap, visited, size, i, j);
        basins.push_back(size);
      }
    }
  }
  return basins;
}
int basins(const std::string& fileName) {
  const auto heightMap = getHeightMap(fileName);
  auto basinSizes = getBasinSizes(heightMap);
  std::nth_element(basinSizes.begin(), basinSizes.begin() + 3, basinSizes.end(),
                   std::greater<int>());
  return basinSizes[0] * basinSizes[1] * basinSizes[2];
}
