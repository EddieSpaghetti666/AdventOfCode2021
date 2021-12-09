#pragma once
#include <string>
#include <vector>

static const std::vector<std::pair<int, int>> OFFSETS = {
    {0, -1}, {0, 1}, {-1, 0}, {1, 0}};

int riskLevel(const std::string& fileName);
int basins(const std::string& fileName);
