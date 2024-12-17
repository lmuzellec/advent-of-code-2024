#include <chrono>
#include <vector>
#include <map>
#include <queue>
#include <unordered_set>

#include "utils.hpp"
#include "graph.hpp"

std::map<Direction, int> dX({{Direction::UP, 0}, {Direction::RIGHT, 1}, {Direction::DOWN, 0}, {Direction::LEFT, -1}});
std::map<Direction, int> dY({{Direction::UP, -1}, {Direction::RIGHT, 0}, {Direction::DOWN, 1}, {Direction::LEFT, 0}});

std::pair<std::unordered_map<Node, long long>, std::unordered_map<Node, Node>> dijkstra(Graph &graph, Node start)
{
  std::unordered_map<Node, long long> distances;
  std::unordered_map<Node, Node> previous;

  for (auto keyValue : graph.connections)
  {
    Node key = keyValue.first;

    distances[key] = __LONG_LONG_MAX__;
  }

  distances[start] = 0;

  std::priority_queue<CostToNode, std::vector<CostToNode>, std::greater<CostToNode>> priority_queue;

  priority_queue.push(std::make_pair(0, start));

  while (!priority_queue.empty())
  {
    CostToNode current = priority_queue.top();
    long long currentCost = current.first;
    Node currentNode = current.second;
    priority_queue.pop();

    for (auto neighbor : graph.connections[currentNode])
    {
      long long neighborCost = neighbor.first;
      Node neighborNode = neighbor.second;

      long long newDistance = currentCost + neighborCost;

      if (newDistance < distances[neighborNode])
      {
        distances[neighborNode] = newDistance;
        previous[neighborNode] = currentNode;

        priority_queue.push(std::make_tuple(newDistance, neighborNode));
      }
    }
  }

  return std::make_pair(distances, previous);
}

long long solve(std::vector<std::string> input)
{
  Graph graph;

  std::pair<int, int> start;
  std::vector<Node> ends;

  for (int directionInt = Direction::UP; directionInt <= Direction::LEFT; directionInt++)
  {
    Direction direction = static_cast<Direction>(directionInt);
    for (int y = 0; y < input.size(); y++)
    {
      for (int x = 0; x < input[0].size(); x++)
      {
        if (input[y][x] == '#')
        {
          continue;
        }

        Node from = std::make_tuple(direction, x, y);

        if (input[y][x] == 'S')
        {
          start = std::make_pair(x, y);
        }
        else if (input[y][x] == 'E')
        {
          ends.push_back(from);
        }

        if (input[y + dY[direction]][x + dX[direction]] == '.' || input[y + dY[direction]][x + dX[direction]] == 'E')
        {
          Node to = std::make_tuple(direction, x + dX[direction], y + dY[direction]);
          graph.addCostedEdge(from, to, 1);
        }

        Direction turnLeft = static_cast<Direction>(utils::positive_modulo(directionInt - 1, 4));
        graph.addCostedEdge(from, std::make_tuple(turnLeft, std::get<1>(from), std::get<2>(from)), 1000);
        Direction turnRight = static_cast<Direction>(utils::positive_modulo(directionInt + 1, 4));
        graph.addCostedEdge(from, std::make_tuple(turnRight, std::get<1>(from), std::get<2>(from)), 1000);
      }
    }
  }

  auto distancesAndPrevious = dijkstra(graph, std::make_tuple(Direction::RIGHT, start.first, start.second));

  auto distances = distancesAndPrevious.first;
  auto previous = distancesAndPrevious.second;

  long long min = __LONG_LONG_MAX__;

  for (auto end : ends)
  {
    min = std::min(min, distances[end]);
  }

  return min;
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