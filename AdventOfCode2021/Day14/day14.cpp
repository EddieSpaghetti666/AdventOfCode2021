#include "day14.h"

#include <algorithm>
#include <cassert>
#include <map>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

#include "../common.h"

using PolymerRules = std::map<std::string, std::string>;

PolymerRules getPolymerRules(const std::vector<std::string>& instructions) {
  PolymerRules rules;
  auto regex = std::regex("(\\w\\w) -> (\\w)");
  auto matchResults = std::smatch();
  for (const auto& rule : instructions) {
    std::regex_search(rule, matchResults, regex);
    if (matchResults.empty()) continue;
    assert(matchResults.size() ==
           3);  // 1 for overall match, 2 for each part of the polymer rule.
    auto lhs = matchResults[1].str();
    auto production = matchResults[2].str();
    assert(production.size() == 1);
    rules[lhs] = production;
  }
  return rules;
}

std::vector<std::string> initialPolymerPairs(
    const std::string& initialPolymer) {
  std::vector<std::string> pairs;
  std::transform(initialPolymer.cbegin(), initialPolymer.cend() - 1,
                 initialPolymer.cbegin() + 1, std::back_inserter(pairs),
                 [](const char element1, const char element2) {
                   std::string pair;
                   pair += element1;
                   pair += element2;
                   return pair;
                 });
  return pairs;
}

std::map<std::string, unsigned long long> elementPairCounts(
    const PolymerRules& rules, const std::vector<std::string>& initialPairs,
    const int steps) {
  std::map<std::string, unsigned long long> pairCounts;
  for (auto pair : initialPairs) {
    pairCounts[pair]++;
  }
  for (int i = 0; i < steps; ++i) {
    auto newCounts = pairCounts;
    for (const auto& rule : rules) {
      for (const auto& pc : pairCounts) {
        auto pair = pc.first;
        if (rule.first == pair) {
          const auto occur = pc.second;
          newCounts[pair] -= occur;
          const std::string firstNewPair = pair[0] + rule.second;
          const std::string secondNewPiar = rule.second + pair[1];
          newCounts[firstNewPair] += occur;
          newCounts[secondNewPiar] += occur;
        }
      }
    }
    pairCounts = newCounts;
  }
  return pairCounts;
}

std::map<char, unsigned long long> buildElementCounts(
    const std::map<std::string, unsigned long long> pairCounts) {
  std::map<char, size_t> counts;
  for (const auto& pc : pairCounts) {
    const auto pair = pc.first;
    const auto occur = pc.second;
    counts[pair[0]] += occur;
    counts[pair[1]] += occur;
  }
  return counts;
}

unsigned long long polymerScore(const std::string& fileName, const int steps) {
  auto polymerInstruction = parseInputToVector<std::string>(fileName);
  const auto startPolymer = polymerInstruction[0];
  const auto rules = getPolymerRules(polymerInstruction);
  auto pairCounts =
      elementPairCounts(rules, initialPolymerPairs(startPolymer), steps);
  auto elementCounts = buildElementCounts(pairCounts);
  elementCounts[startPolymer[0]]++;
  elementCounts[startPolymer[1]]++;
  auto [highest, lowest] =
      std::minmax_element(elementCounts.cbegin(), elementCounts.cend(),
                          [](const auto& pair1, const auto& pair2) {
                            return pair2.second < pair1.second;
                          });
  auto h = std::llround(highest->second / 2.0);
  auto l = std::llround(lowest->second / 2.0);
  return h - l;
}
