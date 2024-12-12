#pragma once

#include <vector>

struct GraphNode;
struct Connection
{
  GraphNode *ptr;
};

struct GraphNode
{
  int x;
  int y;
  char plant;
  std::vector<Connection> connections;
  int diffConnections;
  bool operator==(const GraphNode &other) const;
};

bool GraphNode::operator==(const GraphNode &other) const
{
  return x == other.x && y == other.y;
}

template <>
struct std::hash<GraphNode>
{
  std::size_t operator()(const GraphNode &s) const noexcept
  {
    std::size_t h1 = std::hash<int>{}(s.x);
    std::size_t h2 = std::hash<int>{}(s.y);
    return h1 ^ (h2 << 1);
  }
};