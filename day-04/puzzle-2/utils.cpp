#include "utils.hpp"

namespace utils
{
  std::vector<std::string> parseInput()
  {
    std::string line;
    std::vector<std::string> result;

    while (std::getline(std::cin, line))
    {
      result.push_back(line);
    }

    return result;
  }
}