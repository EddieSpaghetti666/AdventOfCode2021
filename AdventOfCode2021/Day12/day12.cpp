#include "day12.h"

#include <algorithm>
#include <cstring>
#include <functional>
#include <map>
#include <queue>
#include <string>
#include <utility>
#include <set>

#include "../common.h"

using Graph = std::map<std::string, std::vector<std::string>>;
using Path = std::vector<std::string>;

std::pair<std::string, std::string> getVertices(const std::string& connection) {
  // I'm assuming that the connection is of the form 'vertex1-vertex2' !
  auto seperator = std::find(connection.begin(), connection.end(), '-');
  return std::make_pair(std::string(connection.begin(), seperator),
                        std::string(seperator + 1, connection.end()));
}

Graph createCaveGraph(const Path& caveMap) {
  Graph caveGraph;
  for (auto connection : caveMap) {
    auto [vertex1, vertex2] = getVertices(connection);
    caveGraph[vertex1].push_back(vertex2);
    caveGraph[vertex2].push_back(vertex1);
  }
  return caveGraph;
}

bool isBig(const std::string& cave) {
  return std::all_of(cave.begin(), cave.end(), isupper);
}

bool canVisit(const Path& path,
                    const std::string& cave) {
  return isBig(cave) || std::find(path.begin(), path.end(), cave) == path.end();
}

int pathCount(
    const Graph& caveGraph,
    std::function<bool(const Path&, const std::string&)>
        canVisit) {
  std::vector<Path> paths;
  std::queue<Path> queue;
  queue.push({"start"});
  const auto END = "end";
  while (!queue.empty()) {
    auto currentPath = queue.front();
    queue.pop();

    auto lastVertex = currentPath.back();
    if (lastVertex == END) {
      paths.push_back(currentPath);
    } else {
      const auto connectedVerteces = caveGraph.at(lastVertex);
      for (auto vertex : connectedVerteces) {
        if (canVisit(currentPath, vertex)) {
          auto path(currentPath);
          path.push_back(vertex);
          queue.push(path);
        }
      }
    }
  }
  return paths.size();
}

int totalPaths(const std::string& fileName) {
  const auto caveMap = parseInputToVector<std::string>(fileName);
  auto caveGraph = createCaveGraph(caveMap);
  return pathCount(caveGraph, canVisit);
}

bool canVisit2(Path path, const std::string& cave) {
  if (canVisit(path, cave))
    return true;
  else if (cave == "start" || cave == "end")
    return false;
  else {
    //This is extremely inefficient! 
    Path smallCaves;
    std::copy_if(path.begin(), path.end(), std::back_inserter(smallCaves),
                 [](auto cave) { return !isBig(cave); });

    //check if there are 2 of one small cave on the path already
    std::sort(smallCaves.begin(), smallCaves.end());
    return std::adjacent_find(smallCaves.begin(), smallCaves.end()) ==
           smallCaves.end();
  }
}

int totalPaths2(const std::string& fileName) {
  const auto caveMap = parseInputToVector<std::string>(fileName);
  const auto caveGraph = createCaveGraph(caveMap);
  return pathCount(caveGraph, canVisit2);
}
