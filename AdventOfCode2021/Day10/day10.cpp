#include "day10.h"

#include <assert.h>

#include <algorithm>
#include <deque>
#include <map>
#include <numeric>
#include <optional>
#include <stack>

#include "../common.h"

bool bracesMatch(char openBrace, char closeBrace) {
  switch (openBrace) {
    case '(':
      return closeBrace == ')';
    case '[':
      return closeBrace == ']';
    case '{':
      return closeBrace == '}';
    case '<':
      return closeBrace == '>';
    default:
      assert(false);  // unreachable
  }
}

bool isOpenBrace(const char brace) {
  return brace == '{' || brace == '(' || brace == '[' || brace == '<';
}

bool isClosingBrace(const char brace) {
  return brace == '}' || brace == ')' || brace == ']' || brace == '>';
}

std::optional<char> firstMismatch(const std::string& line) {
  // I am assuming that the line only contains open and close braces!

  std::stack<char> braces;
  for (const char b : line) {
    if (isOpenBrace(b)) {
      braces.push(b);
      continue;
    }

    assert(isClosingBrace(b));

    if (!bracesMatch(braces.top(), b))
      return b;
    else
      braces.pop();
  }
  return {};
}
int syntaxScore(const std::string& fileName) {
  const auto lines = parseInputToVector<std::string>(fileName);
  std::map<char, int> braceScores = {
      {')', 3}, {']', 57}, {'}', 1197}, {'>', 25137}};

  return std::accumulate(
      lines.begin(), lines.end(), 0, [=](auto accum, auto line) mutable {
        auto badBrace = firstMismatch(line);
        return badBrace ? accum + braceScores[*badBrace] : accum;
      });
}

char matchingCloseBrace(const char b) {
  const std::map<char, char> matchingBraces = {
      {'(', ')'}, {'[', ']'}, {'{', '}'}, {'<', '>'}};
  return matchingBraces.find(b)->second;
}

std::optional<std::string> completionPattern(const std::string& line) {
  std::deque<char> braces;
  for (const char b : line) {
    if (isOpenBrace(b)) {
      braces.push_front(b);
      continue;
    }

    assert(isClosingBrace(b));

    if (!bracesMatch(braces.front(), b))
      return {};
    else
      braces.pop_front();
  }
  std::string pattern;
  std::transform(braces.begin(), braces.end(), std::back_inserter(pattern),
                 matchingCloseBrace);
  return pattern;
}

unsigned long long score(const std::string& pattern) {
  // Assume that pattern only contains chars that have a corresponding score.
  std::map<char, int> braceScores = {{')', 1}, {']', 2}, {'}', 3}, {'>', 4}};
  unsigned long long total = 0;
  for (const char c : pattern) {
    total *= 5;
    total += braceScores[c];
  }
  return total;
}

unsigned long long middleScore(std::vector<std::string> patterns) {
  auto middle = patterns.begin() + patterns.size() / 2;
  std::nth_element(
      patterns.begin(), middle, patterns.end(),
      [](const std::string& pattern1, const std::string& pattern2) {
        return score(pattern1) < score(pattern2);
      });
  return score(*middle);
}
unsigned long long autocompleteScore(const std::string& fileName) {
  const auto lines = parseInputToVector<std::string>(fileName);
  std::vector<std::string> patterns;
  for (const auto& line : lines) {
    auto completePattern = completionPattern(line);
    if (completePattern) {
      patterns.push_back(completePattern.value());
    }
  }

  return middleScore(patterns);
}
