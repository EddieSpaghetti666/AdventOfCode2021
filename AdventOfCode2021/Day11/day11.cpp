#include "day11.h"

#include <cassert>
#include <vector>

#include "../common.h"

bool validCoord(const std::vector<std::vector<int>>& energyLevels, const int i,
                const int j) {
  return i >= 0 && i < energyLevels.size() && j >= 0 &&
         j < energyLevels[i].size();
}

void flash(std::vector<std::vector<int>>& energyLevels,
           std::vector<std::vector<bool>>& flashed, const int i, const int j,
           int& flashes) {
  static const std::vector<std::pair<int, int>> OFFSETS = {
      {0, -1}, {0, 1}, {-1, 0}, {1, 0}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}};

  assert(!flashed[i][j]);
  energyLevels[i][j] = 0;
  flashed[i][j] = true;
  flashes++;
  for (const auto& offset : OFFSETS) {
    int k = i + offset.first;
    int l = j + offset.second;
    if (validCoord(energyLevels, k, l) && !flashed[k][l]) {
      energyLevels[k][l]++;
      if (energyLevels[k][l] > 9) flash(energyLevels, flashed, k, l, flashes);
    }
  }
}

int step(std::vector<std::vector<int>>& energyLevels) {
  std::vector<std::vector<bool>> flashed(
      energyLevels.size(), std::vector<bool>(energyLevels[0].size(), false));

  for (auto& row : energyLevels) {
    for (int& energy : row) {
      ++energy;
    }
  }

  int flashes = 0;

  for (int i = 0; i < energyLevels.size(); ++i) {
    for (int j = 0; j < energyLevels[i].size(); ++j) {
      if (energyLevels[i][j] > 9) {
        flash(energyLevels, flashed, i, j, flashes);
      }
    }
  }

  return flashes;
}
int totalFlashes(const std::string& fileName) {
  auto energyLevels = as2DVector(fileName);
  int flashes = 0;
  for (int i = 0; i < 100; ++i) {
    flashes += step(energyLevels);
  }

  return flashes;
}
bool synced(const std::vector<std::vector<int>>& energyLevels) {
  for (const auto& row : energyLevels) {
    //check if entire row is the same by compare each element to the one after.
    if (!std::equal(row.begin() + 1, row.end(), row.begin())) return false;
  }
  return true;
}
int firstSync(const std::string& fileName) {
  auto energyLevels = as2DVector(fileName);
  int steps = 0;
  while (!synced(energyLevels)) {
    step(energyLevels);
    ++steps;
  }

  return steps;
}
