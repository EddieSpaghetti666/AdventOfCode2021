#include "day2.h"
#include <sstream>

int submarinePosition(const std::vector<std::string>& commands)
{
	int horizontal = 0;
	int depth = 0;
	for(const auto& command : commands){
		std::stringstream ss(command);
		std::string direction;
		ss >> direction;
		int magnitude = 0;
		ss >> magnitude;
		if(direction == "forward"){
			horizontal += magnitude;
		}
		else if(direction == "up"){
			depth -= magnitude;
		}
		else if(direction == "down"){
			depth += magnitude;
		}
	}
	return horizontal * depth;
}

int aimSubmarinePosition(const std::vector<std::string>& commands)
{
	int horizontal = 0;
	int depth = 0;
	int aim = 0;
	for(const auto& command : commands){
		std::stringstream ss(command);
		std::string direction;
		ss >> direction;
		int magnitude = 0;
		ss >> magnitude;
		if(direction == "forward"){
			horizontal += magnitude;
			depth += magnitude*aim;
		}
		else if(direction == "up"){
			aim -= magnitude;
		}
		else if(direction == "down"){
			aim += magnitude;
		}
	}
	return horizontal * depth;
}

