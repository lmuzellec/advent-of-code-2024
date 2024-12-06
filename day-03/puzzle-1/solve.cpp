#include <vector>
#include <regex>

#include "utils.hpp"

long solve()
{
  long sum = 0;
  std::vector<std::string> lines = utils::parseInput();

  std::regex mul_regex("mul\\(([1-9]|[1-9]\\d{1,2}),(\\d|[1-9]\\d{1,2})\\)");

  for (auto line : lines)
  {
    auto mul_begin = std::sregex_iterator(line.begin(), line.end(), mul_regex);
    auto mul_end = std::sregex_iterator();

    for (std::sregex_iterator i = mul_begin; i != mul_end; ++i)
    {
      std::smatch match = *i;
      std::string complete = match[0].str();
      std::string left = match[1].str();
      std::string right = match[2].str();

      long leftL = std::stol(left);
      long rightL = std::stol(right);

      sum += leftL * rightL;
    }
  }

  return sum;
}

int main()
{
  long result = solve();
  std::cout << "result: " << result << std::endl;
}