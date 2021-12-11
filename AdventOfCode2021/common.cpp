#include "common.h"


template <>
std::vector<std::string> parseInputToVector(const std::string& fileName) {
  std::vector<std::string> result;
  std::string data;
  std::ifstream file(fileName);

  while (std::getline(file, data, '\n')) {
    result.push_back(data);
  }
  return result;
}


std::vector<std::vector<int>> as2DVector(const std::string& fileName) {
  std::vector<std::vector<int>> twoDVec;
  std::vector<int> row;

  std::fstream file(fileName);
  std::string line;
  while (std::getline(file, line)) {
    std::transform(line.begin(), line.end(), std::back_inserter(row),
                   [](char c) { return c - '0'; });
    twoDVec.push_back(row);
    row.clear();
  }

  return twoDVec;
}


