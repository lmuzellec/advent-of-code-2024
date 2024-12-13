#include <chrono>
#include <vector>
#include <unordered_set>
#include <queue>

#include "utils.hpp"
#include "graph.hpp"

void addPadding(std::vector<std::string> &input)
{
  for (auto &line : input)
  {
    line.insert(line.end(), '.');
    line.insert(line.begin(), '.');
  }

  input.insert(input.end(), std::string(input[0].size(), '.'));
  input.insert(input.begin(), std::string(input[0].size(), '.'));
}

int bfs(GraphNode &node, std::unordered_set<GraphNode> &globalVisited)
{
  int sides = 0;
  std::queue<GraphNode> q;
  std::unordered_set<GraphNode> visited;

  q.push(node);

  while (!q.empty())
  {
    GraphNode current = q.front();
    q.pop();

    if (visited.find(current) == visited.end())
    {
      sides += current.diffConnections;
      visited.insert(current);
      globalVisited.insert(current);

      for (auto connected : current.connections)
      {
        GraphNode neighbour = *connected.ptr;
        q.push(neighbour);
      }
    }
  }

  return sides * visited.size();
}

long solve(std::vector<std::string> input)
{
  addPadding(input);

  std::unordered_set<GraphNode> globalVisited;
  std::vector<std::vector<GraphNode>> nodes(input.size(), std::vector<GraphNode>(input[0].size()));

  for (int y = 0; y < input.size(); y++)
  {
    for (int x = 0; x < input[0].size(); x++)
    {
      nodes[y][x] = GraphNode(x, y, input[y][x], std::vector<Connection>(), 0);
    }
  }

  for (int y = 1; y < input.size() - 1; y++)
  {
    for (int x = 1; x < input[0].size() - 1; x++)
    {
      GraphNode &node = nodes[y][x];

      if (nodes[y][x - 1].plant == node.plant)
      {
        node.connections.push_back(Connection{&nodes[y][x - 1]});
      }
      else if (nodes[y + 1][x - 1].plant == node.plant && nodes[y + 1][x].plant == node.plant ||
               nodes[y + 1][x].plant != node.plant)
      {
        node.diffConnections++;
      }

      if (nodes[y - 1][x].plant == node.plant)
      {
        node.connections.push_back(Connection{&nodes[y - 1][x]});
      }
      else if (nodes[y - 1][x - 1].plant == node.plant && nodes[y][x - 1].plant == node.plant ||
               nodes[y][x - 1].plant != node.plant)
      {
        node.diffConnections++;
      }

      if (nodes[y][x + 1].plant == node.plant)
      {
        node.connections.push_back(Connection{&nodes[y][x + 1]});
      }
      else if (nodes[y - 1][x].plant == node.plant && nodes[y - 1][x + 1].plant == node.plant ||
               nodes[y - 1][x].plant != node.plant)
      {
        node.diffConnections++;
      }

      if (nodes[y + 1][x].plant == node.plant)
      {
        node.connections.push_back(Connection{&nodes[y + 1][x]});
      }
      else if (nodes[y][x + 1].plant == node.plant && nodes[y + 1][x + 1].plant == node.plant ||
               nodes[y][x + 1].plant != node.plant)
      {
        node.diffConnections++;
      }
    }
  }

  long result = 0;

  for (int y = 1; y < input.size() - 1; y++)
  {
    for (int x = 1; x < input[0].size() - 1; x++)
    {
      GraphNode &node = nodes[y][x];

      if (globalVisited.find(node) == globalVisited.end())
      {
        result += bfs(node, globalVisited);
      }
    }
  }

  return result;
}

int main()
{
  std::vector<std::string> input = utils::parseInput();

  using milli = std::chrono::milliseconds;
  auto start = std::chrono::high_resolution_clock::now();

  long long result = solve(input);

  auto finish = std::chrono::high_resolution_clock::now();
  std::cout << "result: " << result << std::endl;

  std::cout << "took "
            << std::chrono::duration_cast<milli>(finish - start).count()
            << " ms" << std::endl;
}