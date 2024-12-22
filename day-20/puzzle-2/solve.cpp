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
    auto x = current.first;
    auto y = current.second;

    for (int dx = -20; dx <= 20; dx++)
    {
      for (int dy = std::abs(dx) - 20; dy <= 20 - std::abs(dx); dy++)
      {
        if (x + dx >= 0 &&
            x + dx < map.size().first &&
            y + dy >= 0 &&
            y + dy < map.size().second &&
            map.getAt({x + dx, y + dy}) &&
            (distances[current] - distances[{x + dx, y + dy}] - (std::abs(dx) + std::abs(dy)) >= 100))
        {
          result++;
        }
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