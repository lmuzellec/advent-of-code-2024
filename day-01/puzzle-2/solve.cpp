#include <iostream>
#include <vector>
#include <set>

#include "utils.hpp"

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

long solve()
{
  long sum = 0;
  std::vector<std::string> lines = parseInput();

  std::vector<long> leftList;
  std::vector<long> rightList;

  for (auto line : lines)
  {
    std::vector<std::string> numbers = split(line, "   ");

    leftList.push_back(std::stol(numbers[0]));
    rightList.push_back(std::stol(numbers[1]));
  }

  std::unordered_map<long, long> leftInRight;

  for (auto left : leftList)
  {
    leftInRight[left] = 0;
  }

  for (auto right : rightList)
  {
    if (leftInRight.find(right) != leftInRight.end())
    {
      leftInRight[right] += 1;
    }
  }

  for (auto left : leftList)
  {
    if (leftInRight.find(left) != leftInRight.end())
    {
      long appearance = left * leftInRight[left];
      sum += appearance;
    }
  }

  return sum;
}

int main()
{
  long result = solve();
  std::cout << "result: " << result << std::endl;
}