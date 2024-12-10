#include <vector>
#include <string>
#include <stack>
#include <unordered_set>

#include "utils.hpp"
#include "graph.hpp"

int dfs(GraphNode start)
{
  int result = 0;
  std::stack<GraphNode> s;
  s.push(start);

  while (!s.empty())
  {
    GraphNode current = s.top();
    s.pop();

    if (current.height == 9)
    {
      result++;
    }

    for (auto neighbour : current.connections)
    {
      GraphNode n = *neighbour.ptr;
      s.push(n);
    }
  }

  return result;
}

unsigned long long solve()
{
  std::vector<std::string> map = utils::parseInput();

  std::vector<std::vector<GraphNode>> nodes = std::vector<std::vector<GraphNode>>(map.size(), std::vector<GraphNode>(map[0].size()));

  for (int y = 0; y < map.size(); y++)
  {
    for (int x = 0; x < map[0].size(); x++)
    {
      nodes[y][x] = GraphNode{x, y, map[y][x] - '0', std::vector<Connection>()};
    }
  }

  for (int y = 0; y < nodes.size(); y++)
  {
    for (int x = 0; x < nodes[0].size(); x++)
    {
      GraphNode &node = nodes[y][x];

      if (x - 1 >= 0 && nodes[y][x - 1].height == node.height + 1)
      {
        node.connections.push_back(Connection{&nodes[y][x - 1]});
      }

      if (y - 1 >= 0 && nodes[y - 1][x].height == node.height + 1)
      {
        node.connections.push_back(Connection{&nodes[y - 1][x]});
      }

      if (x + 1 < nodes[0].size() && nodes[y][x + 1].height == node.height + 1)
      {
        node.connections.push_back(Connection{&nodes[y][x + 1]});
      }

      if (y + 1 < nodes.size() && nodes[y + 1][x].height == node.height + 1)
      {
        node.connections.push_back(Connection{&nodes[y + 1][x]});
      }
    }
  }

  int sum = 0;

  for (int y = 0; y < map.size(); y++)
  {
    for (int x = 0; x < map[0].size(); x++)
    {
      if (nodes[y][x].height == 0)
      {
        sum += dfs(nodes[y][x]);
      }
    }
  }

  return sum;
}

int main()
{
  unsigned long long result = solve();
  std::cout << "result: " << result << std::endl;
}