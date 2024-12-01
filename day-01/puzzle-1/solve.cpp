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

  std::sort(leftList.begin(), leftList.end());
  std::sort(rightList.begin(), rightList.end());

  for (int i = 0; i < lines.size(); i++)
  {
    long diff = std::abs(leftList[i] - rightList[i]);
    sum += diff;
  }

  return sum;
}

int main()
{
  long result = solve();
  std::cout << "result: " << result << std::endl;
}