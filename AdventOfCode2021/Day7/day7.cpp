#include "day7.h"

#include <algorithm>
#include <numeric>

#include "../common.h"
int median(std::vector<int>& crabLocations) {
  const size_t med = crabLocations.size() / 2;
  std::nth_element(crabLocations.begin(), crabLocations.begin() + med,
                   crabLocations.end());
  return crabLocations[med];
}

int mean(const std::vector<int> crabLocations) {
  double mean = std::accumulate(crabLocations.begin(), crabLocations.end(), 0.0f) /
         crabLocations.size();
  return std::round(mean);
}

int costToMoveAll(const std::vector<int>& crabLocations, const int dest) {
  int total = 0;
  for (const auto location : crabLocations) {
    total += std::abs(dest - location);
  }
  return total;
}

int leastFuel(const std::string& fileName) {
  auto crabLocations = parseInputToVector<int>(fileName);
  const int med = median(crabLocations);
  const int cost = costToMoveAll(crabLocations, med);

  return cost;
}

int costToMoveAll2(const std::vector<int>& crabLocations, const int dest){
  int total = 0;
  for(const auto location : crabLocations){
    int diff = std::abs((dest - location));
    for(int i = 1; i <= diff; ++i){
      total += i;
    }
  }
  return total;
}

int leastFuel2(const std::string& fileName){
  auto crabLocations = parseInputToVector<int>(fileName);
  const int m = mean(crabLocations);
  const int cost = costToMoveAll2(crabLocations, m);

  return cost;
}
