#include "day3.h"

#include <algorithm>
#include <functional>

char mostCommonBit(std::vector<std::string> numbers, int place) {
  int ones = 0;
  char mostCommonBit;
  for (const std::string& number : numbers) {
    if (number[place] == '1') ones++;
  }
  if (ones >= numbers.size() - ones) {
    mostCommonBit = '1';
  } else {
    mostCommonBit = '0';
  }
  return mostCommonBit;
}

int binaryDiagnostic(const std::vector<std::string>& numbers) {
  size_t numberSize = numbers[0].size();
  std::string gamma, epsilon;
  for (int i = 0; i < numberSize; ++i) {
    gamma += mostCommonBit(numbers, i);
    epsilon += mostCommonBit(numbers, i) == '1' ? '0' : '1';
  }
  int gammaVal = stoi(gamma, 0, 2);
  int epsilonVal = stoi(epsilon, 0, 2);

  return gammaVal * epsilonVal;
}


int rating(std::vector<std::string> numbers,
           std::function<bool(char, char)> comparitor, int place = 0) {
  if (numbers.size() == 1)
    return stoi(numbers[0], 0, 2);
  else {
    std::vector<std::string> filteredNumbers;
    char bit = mostCommonBit(numbers, place);
    std::copy_if(numbers.begin(), numbers.end(),
                 std::back_inserter(filteredNumbers),
                 [place, bit, comparitor](const std::string& number) {
                   return comparitor(number[place], bit);
                 });
    return rating(filteredNumbers, comparitor, place + 1);
  }
}

int lifeSupportRating(const std::vector<std::string>& numbers) {
  int oxygen = rating(numbers, std::equal_to<char>());
  int co2 = rating(numbers, std::not_equal_to<char>());
  return oxygen * co2;
}
