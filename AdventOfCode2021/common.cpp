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

