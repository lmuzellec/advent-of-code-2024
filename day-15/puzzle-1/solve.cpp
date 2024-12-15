#include <chrono>
#include <vector>

#include "utils.hpp"
#include "cell.hpp"
#include "map.hpp"

long solve(std::vector<std::string> input)
{

  std::vector<std::string> lines;

  std::string movements;

  auto it = input.begin();

  for (; *it != ""; it++)
  {
    lines.push_back(*it);
  }

  it++;

  for (; it != input.end(); it++)
  {
    std::string line = *it;

    movements += line;
  }

  Map map(lines);

  for (auto move : movements)
  {
    map.move(move);
    // map.render();
  }

  long result = 0;

  std::vector<std::vector<Cell>> cells = map.getCells();

  for (int y = 0; y < cells.size(); y++)
  {
    for (int x = 0; x < cells.size(); x++)
    {
      auto cell = cells[y][x];
      if (cell.getType() == Cell::kind::box)
      {
        result += 100 * y + x;
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