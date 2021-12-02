#pragma once
#include <fstream>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

template <typename T>
std::vector<T> parseInputToVector(const std::string& fileName) {
  std::vector<T> result;
  T data;
  std::ifstream file(fileName);
  while (file >> data) {
    result.push_back(data);
  }
  return result;
}

template <>
std::vector<std::string> parseInputToVector(const std::string& fileName);

template <typename T, typename R>
R answerFromFileInput(
    const std::string& fileName,
    std::function<R(const std::vector<T>&)> funcWithVectorInput){
  std::vector<T> dataFromFile = parseInputToVector<T>(fileName);
  return funcWithVectorInput(dataFromFile);
}

