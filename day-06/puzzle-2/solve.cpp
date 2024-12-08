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

bool march(
    std::vector<std::string> &map,
    std::set<std::tuple<long, long, Direction>> &visited,
    long x,
    long y,
    Direction direction)
{
  if (x < 0 || x >= map[0].size() || y < 0 || y >= map.size())
  {
    return false;
  }

  if (visited.find(std::make_tuple(x, y, direction)) != visited.end())
  {
    return true;
  }

  visited.insert(std::make_tuple(x, y, direction));

  switch (direction)
  {
  case Direction::UP:
    if (y - 1 >= 0 && map[y - 1][x] == '#')
    {
      return march(map, visited, x, y, Direction::RIGHT);
    }
    else if (y - 1 >= 0)
    {
      return march(map, visited, x, y - 1, Direction::UP);
    }
    return false;
  case Direction::DOWN:
    if (y + 1 < map.size() && map[y + 1][x] == '#')
    {
      return march(map, visited, x, y, Direction::LEFT);
    }
    else if (y + 1 < map.size())
    {
      return march(map, visited, x, y + 1, Direction::DOWN);
    }
    return false;
  case Direction::LEFT:
    if (x - 1 >= 0 && map[y][x - 1] == '#')
    {
      return march(map, visited, x, y, Direction::UP);
    }
    else if (x - 1 >= 0)
    {
      return march(map, visited, x - 1, y, Direction::LEFT);
    }
    return false;
  case Direction::RIGHT:
    if (x + 1 < map[0].size() && map[y][x + 1] == '#')
    {
      return march(map, visited, x, y, Direction::DOWN);
    }
    else
    {
      return march(map, visited, x + 1, y, Direction::RIGHT);
    }
    return false;
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

  long validObstructions = 0;

  long obstructionsToCheck = map.size() * map[0].size();

  for (int y = 0; y < map.size(); y++)
  {
    for (int x = 0; x < map[0].size(); x++)
    {
      std::vector<std::string> alteredMap(map.begin(), map.end());
      alteredMap[y][x] = '#';

      std::cout << 1 + y * map[0].size() + x << '/' << obstructionsToCheck << std::endl;

      std::set<std::tuple<long, long, Direction>> visited;
      if (march(alteredMap, visited, std::get<0>(initialPosition), std::get<1>(initialPosition), std::get<2>(initialPosition)))
      {
        validObstructions++;
      }
    }
  }

  return validObstructions;
}

int main()
{
  long result = solve();
  std::cout << "result: " << result << std::endl;
}