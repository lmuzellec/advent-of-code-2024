#pragma once

#include <set>
#include <vector>
#include <tuple>
#include <unordered_map>

enum Direction
{
  UP,
  RIGHT,
  DOWN,
  LEFT
};

typedef std::tuple<Direction, int, int> Node;

namespace std
{
  template <>
  struct hash<Node>
  {
    std::size_t operator()(const Node &t) const
    {
      std::size_t seed = 0;
      seed ^= std::hash<int>()(static_cast<int>(std::get<0>(t))) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
      seed ^= std::hash<int>()(std::get<1>(t)) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
      seed ^= std::hash<int>()(std::get<2>(t)) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
      return seed;
    }
  };
}

typedef std::pair<long long, Node> CostToNode;

class Graph
{
public:
  std::unordered_map<Node, std::vector<CostToNode>> connections;
  Graph()
  {
    connections = std::unordered_map<Node, std::vector<CostToNode>>();
  }

  void addCostedEdge(Node from, Node to, long long cost)
  {
    connections[from].push_back(std::make_pair(cost, to));
  }
};
