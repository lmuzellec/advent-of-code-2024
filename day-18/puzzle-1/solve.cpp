#include <chrono>
#include <vector>

#include "utils.hpp"
#include "map.hpp"

long solve(std::vector<std::string> input)
{
  std::vector<Position> bytes;

  for (auto line : input)
  {
    auto xy = utils::split(line, ",");

    auto x = xy[0];
    auto y = xy[1];

    bytes.push_back({std::stoi(x), std::stoi(y)});
  }

  Map map;

  for (int i = 0; i < 1024; i++)
  {
    map.corrupt(bytes[i]);
  }

  std::cout << std::endl;
  map.display();

  auto [distances, previous] = map.dijkstra({0, 0});

  long result = distances[{70, 70}];
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