#include "day8.h"

#include <cassert>
#include <map>
#include <regex>
#include <vector>
#include <numeric>

#include "../common.h"

std::vector<std::string> getOutputDigits(const std::string& line) {
  const auto regex =
      std::regex("^[\\w\\s]+\\|\\s*(\\w+) (\\w+) (\\w+) (\\w+)$");
  auto matchResults = std::smatch();
  std::regex_search(line, matchResults, regex);
  assert(matchResults.size() == 5);
  std::vector<std::string> digits(
      matchResults.begin() + 1,  //+1 because the first match is the whole line
      matchResults.end());
  return digits;
}

std::vector<std::string> getOutputDigits(
    const std::vector<std::string>& inputLines) {
  std::vector<std::string> allDigits;
  for (const auto& line : inputLines) {
    const auto outputDigitsInLine = getOutputDigits(line);
    allDigits.insert(allDigits.end(), outputDigitsInLine.begin(),
                     outputDigitsInLine.end());
  }
  return allDigits;
}

std::vector<std::string> getSignalPattern(const std::string& line) {
  const auto regex = std::regex(
      "^(\\w+) (\\w+) (\\w+) (\\w+) (\\w+) (\\w+) (\\w+) (\\w+) (\\w+) (\\w+)");
  auto matchResults = std::smatch();
  std::regex_search(line, matchResults, regex);
  assert(matchResults.size() == 11);

  std::vector<std::string> signalPattern(matchResults.begin() + 1,
                                         matchResults.end());
  return signalPattern;
}

bool isSpecial(const std::string& digit) {
  return digit.size() == 2 || digit.size() == 4 || digit.size() == 3 ||
         digit.size() == 7;
}

int frequencyOfDigits(const std::string& fileName) {
  const auto inputLines = parseInputToVector<std::string>(fileName);
  const auto outputDigits = getOutputDigits(inputLines);

  return std::count_if(outputDigits.begin(), outputDigits.end(), isSpecial);
}

int inFirstNotSecond(std::string first, std::string second) {
  std::sort(first.begin(), first.end());
  std::sort(second.begin(), second.end());
  std::string diff;
  std::set_difference(first.begin(), first.end(), second.begin(), second.end(),
                      std::back_inserter(diff));
  return diff.size();
}

int decodeNumber(const std::vector<std::string>& signalPatterns,
                 const std::vector<std::string> outputNumber) {
  std::string finalNumber = "";

  //'1' and '4' will help determine what the numbers with signal pattern length
  // 5 and 6 are
  const std::string ONE = *std::find_if(
      signalPatterns.begin(), signalPatterns.end(),
      [](const std::string& signal) { return signal.size() == 2; });
  const std::string FOUR = *std::find_if(
      signalPatterns.begin(), signalPatterns.end(),
      [](const std::string& signal) { return signal.size() == 4; });

  // assuming we actually found those signal patterns
  assert(ONE.size() == 2 && FOUR.size() == 4);

  // Rules for signal pattern length 5 numbers
  auto isThree = [ONE](const std::string& number) {
    return inFirstNotSecond(ONE, number) == 0;
  };
  auto isFive = [FOUR](const std::string& number) {
    return inFirstNotSecond(FOUR, number) == 1;
  };
  // and for 6 length ones
  auto isNine = [FOUR](const std::string& number) {
    return inFirstNotSecond(FOUR, number) == 0;
  };
  auto isSix = [ONE](const std::string& number) {
    return inFirstNotSecond(ONE, number) == 1;
  };

  for (const auto& number : outputNumber) {
    auto signalLength = number.size();
    switch (signalLength) {
      case 2:
        finalNumber += '1';
        break;
      case 3:
        finalNumber += '7';
        break;
      case 4:
        finalNumber += '4';
        break;
      case 7:
        finalNumber += '8';
        break;
      case 5: {
        if (isThree(number))
          finalNumber += '3';
        else if (isFive(number))
          finalNumber += '5';
        else
          finalNumber += '2';
        break;
      }
      case 6: {
        if (isNine(number))
          finalNumber += '9';
        else if (isSix(number))
          finalNumber += '6';
        else
          finalNumber += '0';
        break;
      }
      default:
        assert(false);
    }
  }
  return stoi(finalNumber);
}
int totalDigitOutput(const std::string& fileName) {
  const auto inputLine = parseInputToVector<std::string>(fileName);

  int total = 0;
  for (auto& line : inputLine) {
    auto signalPatterns = getSignalPattern(line);
    auto outputNumbers = getOutputDigits(line);
    auto answer = decodeNumber(signalPatterns, outputNumbers);
    total += answer;
  }

  return total;
}
