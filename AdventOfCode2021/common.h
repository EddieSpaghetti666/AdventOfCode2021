#pragma once
#include <fstream>
#include <functional>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

template <typename T>
std::vector<T> parseInputToVector(const std::string& fileName) {
  std::vector<T> result;
  T data;
  std::ifstream file(fileName);
  while (file >> data) {
    if(file.peek() == ',') file.get();
    result.push_back(data);
  }
   return result;
}

template <>
std::vector<std::string> parseInputToVector(const std::string& fileName);

template <typename T>
int answerFromFileInput(
    const std::string& fileName,
    std::function<int(const std::vector<T>&)> funcWithVectorInput){
  std::vector<T> dataFromFile = parseInputToVector<T>(fileName);
  return funcWithVectorInput(dataFromFile);
}

std::vector<std::vector<int>> as2DVector(const std::string& fileName);
