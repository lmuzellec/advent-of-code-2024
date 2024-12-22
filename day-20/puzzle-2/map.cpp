#include <queue>
#include <iostream>
#include "map.hpp"

std::vector<Position> Map::getNeighbors(Position p)
{
  std::vector<Position> neighbors;

  auto [x, y] = p;

  if (x - 1 >= 0 && map[y][x - 1])
  {
    neighbors.push_back({x - 1, y});
  }

  if (y - 1 >= 0 && map[y - 1][x])
  {
    neighbors.push_back({x, y - 1});
  }

  if (x + 1 < map[0].size() && map[y][x + 1])
  {
    neighbors.push_back({x + 1, y});
  }

  if (y + 1 < map.size() && map[y + 1][x])
  {
    neighbors.push_back({x, y + 1});
  }

  return neighbors;
}

std::pair<std::unordered_map<Position, int>, std::unordered_map<Position, Position>> Map::dijkstra(Position start)
{
  std::unordered_map<Position, int> distances;
  std::unordered_map<Position, Position> previous;

  for (int y = 0; y < map.size(); y++)
  {
    for (int x = 0; x < map[0].size(); x++)
    {
      distances[{x, y}] = INT_MAX;
    }
  }

  std::priority_queue<std::pair<int, Position>> pq;

  distances[start] = 0;
  pq.push({0, start});

  while (!pq.empty())
  {
    auto [cost, current] = pq.top();
    pq.pop();

    std::vector<Position> neighbors = getNeighbors(current);

    for (auto n : neighbors)
    {
      if (distances[n] > distances[current] + 1)
      {
        distances[n] = distances[current] + 1;
        previous[n] = current;
        pq.push({distances[n], n});
      }
    }
  }

  return {distances, previous};
}

void Map::display()
{

  for (int y = 0; y < map.size(); y++)
  {
    for (int x = 0; x < map[0].size(); x++)
    {
      std::cout << (map[y][x] ? '.' : '#');
    }
    std::cout << std::endl;
  }
}

Map::Map(std::vector<std::string> input)
{
  map = std::vector<std::vector<bool>>(input.size(), std::vector<bool>(input[0].size(), false));

  for (int y = 0; y < input.size(); y++)
  {
    for (int x = 0; x < input[0].size(); x++)
    {
      map[y][x] = input[y][x] != '#';

      if (input[y][x] == 'S')
      {
        start = {x, y};
      }

      if (input[y][x] == 'E')
      {
        end = {x, y};
      }
    }
  }
}