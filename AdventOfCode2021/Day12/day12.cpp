#include "day12.h"

#include <algorithm>
#include <cstring>
#include <functional>
#include <map>
#include <queue>
#include <string>
#include <utility>

#include "../common.h"

using Graph = std::map<std::string, std::vector<std::string>>;

std::pair<std::string, std::string> getVertices(const std::string& connection) {
  // I'm assuming that the connection is of the form 'vertex1-vertex2' !
  auto seperator = std::find(connection.begin(), connection.end(), '-');
  return std::make_pair(std::string(connection.begin(), seperator),
                        std::string(seperator + 1, connection.end()));
}

Graph createCaveGraph(const std::vector<std::string>& caveMap) {
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

bool canBeRevisited(const std::vector<std::string>& path,
                    const std::string& cave) {
  return isBig(cave) || std::find(path.begin(), path.end(), cave) == path.end();
}

int pathCount(
    const Graph caveGraph,
    std::function<bool(const std::vector<std::string>&, const std::string&)>
        canVisit) {
  std::vector<std::vector<std::string>> paths;
  std::queue<std::vector<std::string>> queue;
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

  return pathCount(caveGraph, canBeRevisited);
}

bool canVisit2(std::vector<std::string> path, const std::string& cave) {
  if (canBeRevisited(path, cave))
    return true;
  else if (cave == "start" || cave == "end")
    return false;
  else {
    //This is extremelly inefficient! 
    std::vector<std::string> noBigCaves;
    std::copy_if(path.begin(), path.end(), std::back_inserter(noBigCaves),
                 [](auto cave) { return !isBig(cave); });
    std::sort(noBigCaves.begin(), noBigCaves.end());
    return std::adjacent_find(noBigCaves.begin(), noBigCaves.end()) ==
           noBigCaves.end();
  }
}

int totalPaths2(const std::string& fileName) {
  const auto caveMap = parseInputToVector<std::string>(fileName);
  const auto caveGraph = createCaveGraph(caveMap);
  auto answer = pathCount(caveGraph, canVisit2);
  return pathCount(caveGraph, canVisit2);
}
