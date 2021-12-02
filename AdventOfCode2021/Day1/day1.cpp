#include "day1.h"
#include "..\common.h"

int depthIncreases(const std::string& fileName){
	std::vector<int> depthData = parseInputToVector<int>(fileName);
	return depthIncreases(depthData);
}
int depthIncreases(const std::vector<int>& depthData)
{
	int result = 0;
	int lastDepth = depthData[0];
	for(int i = 1; i < depthData.size(); ++i){
		if(depthData[i] > lastDepth) result++;
		lastDepth = depthData[i];
	}
	return result;
}

int windowDepthIncreases(const std::string& fileName){
	std::vector<int> depthData = parseInputToVector<int>(fileName);
	return windowDepthIncreases(depthData);
}

int windowDepthIncreases(const std::vector<int>& inputData)
{
	int result = 0;
	int lastWindow = inputData[0] + inputData[1] + inputData[2];
	for(int i = 3; i < inputData.size(); ++i){
		int nextWindow = inputData[i - 2] + inputData[i - 1] + inputData[i];
		if(nextWindow > lastWindow) result++;
		lastWindow = nextWindow;
	}
	return result;
}

