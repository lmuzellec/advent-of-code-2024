#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <tuple>
#include <set>

#include "utils.hpp"

enum class Direction
{
  UP,
  DOWN,
  LEFT,
  RIGHT
};

void march(
    std::vector<std::string> &map,
    std::vector<std::string> &visitedMap,
    std::set<std::tuple<long, long, Direction>> &visited,
    long x,
    long y,
    Direction direction)
{
  if (x < 0 || x >= map[0].size() || y < 0 || y >= map.size())
  {
    return;
  }

  if (visited.find(std::make_tuple(x, y, direction)) != visited.end())
  {
    return;
  }

  visitedMap[y][x] = 'X';
  visited.insert(std::make_tuple(x, y, direction));

  switch (direction)
  {
  case Direction::UP:
    if (y - 1 >= 0 && map[y - 1][x] == '#')
    {
      return march(map, visitedMap, visited, x, y, Direction::RIGHT);
    }
    else if (y - 1 >= 0)
    {
      return march(map, visitedMap, visited, x, y - 1, Direction::UP);
    }
    return;
  case Direction::DOWN:
    if (y + 1 < map.size() && map[y + 1][x] == '#')
    {
      return march(map, visitedMap, visited, x, y, Direction::LEFT);
    }
    else if (y + 1 < map.size())
    {
      return march(map, visitedMap, visited, x, y + 1, Direction::DOWN);
    }
    return;
  case Direction::LEFT:
    if (x - 1 >= 0 && map[y][x - 1] == '#')
    {
      return march(map, visitedMap, visited, x, y, Direction::UP);
    }
    else if (x - 1 >= 0)
    {
      return march(map, visitedMap, visited, x - 1, y, Direction::LEFT);
    }
    return;
  case Direction::RIGHT:
    if (x + 1 < map[0].size() && map[y][x + 1] == '#')
    {
      return march(map, visitedMap, visited, x, y, Direction::DOWN);
    }
    else
    {
      return march(map, visitedMap, visited, x + 1, y, Direction::RIGHT);
    }
    return;
  }
}

long solve()
{
  std::vector<std::string> map = utils::parseInput();
  std::vector<std::string> visitedMap(map.size(), std::string(map[0].size(), '.'));

  std::tuple<long, long, Direction> initialPosition;

  for (int x = 0; x < map.size(); x++)
  {
    for (int y = 0; y < map[0].size(); y++)
    {
      if (map[y][x] == '^')
      {
        initialPosition = std::make_tuple(x, y, Direction::UP);
        goto initializedInitialPosition;
      }
    }
  }
initializedInitialPosition:

  std::set<std::tuple<long, long, Direction>> visited;

  march(map, visitedMap, visited, std::get<0>(initialPosition), std::get<1>(initialPosition), std::get<2>(initialPosition));

  long positionVisited = 0;
  for (int x = 0; x < visitedMap.size(); x++)
  {
    for (int y = 0; y < visitedMap[0].size(); y++)
    {
      if (visitedMap[y][x] == 'X')
      {
        positionVisited++;
      }
    }
  }

  return positionVisited;
}

int main()
{
  long result = solve();
  std::cout << "result: " << result << std::endl;
}