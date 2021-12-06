#include "day6.h"

#include <map>
#include <numeric>
#include <vector>

#include "../common.h"

void oneDay(std::map<int, long long>& fishCounts) {
  for (auto& fishType : fishCounts) {
    int daysUntilReproduce = fishType.first;
    auto& count = fishType.second;
    if (daysUntilReproduce == 0) {
      fishCounts[7] += count;
      fishCounts[9] += count;
    } else {
      fishCounts[daysUntilReproduce - 1] += count;
    }
    count = 0;
  }
}

void initFishCounts(std::map<int, long long>& fishCounts,
                    const std::vector<int>& startingFish) {
  for (int i = 0; i < 9; ++i) {
    fishCounts[i] = 0;
  }
  for (int fish : startingFish) {
    fishCounts[fish]++;
  }
}

long long totalLanternFish(const std::string& fileName, int days) {
  std::vector<int> startingFish = parseInputToVector<int>(fileName);
  std::map<int, long long> fishCounts;

  initFishCounts(fishCounts, startingFish);

  for (int day = 1; day <= days; ++day) {
    oneDay(fishCounts);
  }

  // add up all the total lantern fish counts.
  const auto answer = std::accumulate(
      fishCounts.begin(), fishCounts.end(), 0LL,
      [](auto a, auto fishType) {
        return fishType.second + a;
      });

  return answer;
}
