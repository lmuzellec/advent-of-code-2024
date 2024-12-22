#include <chrono>
#include <vector>

#include "utils.hpp"
#include "map.hpp"

long long solve(std::vector<std::string> input)
{
  Map map(input);

  auto distanceAndPath = map.dijkstra(map.end);
  auto distances = distanceAndPath.first;
  auto previous = distanceAndPath.second;

  long long result = 0;

  for (Position current = map.start; previous.find(current) != previous.end(); current = previous[current])
  {

    auto [x, y] = current;

    if (x - 2 >= 0 && map.getAt({x - 2, y}) && (distances[current] - distances[{x - 2, y}] - 2 >= 100))
    {
      result++;
    }

    if (y - 2 >= 0 && map.getAt({x, y - 2}) && (distances[current] - distances[{x, y - 2}] - 2 >= 100))
    {
      result++;
    }

    if (x + 2 < map.size().first && map.getAt({x + 2, y}) && (distances[current] - distances[{x + 2, y}] - 2 >= 100))
    {
      result++;
    }

    if (y + 2 < map.size().second && map.getAt({x, y + 2}) && (distances[current] - distances[{x, y + 2}] - 2 >= 100))
    {
      result++;
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