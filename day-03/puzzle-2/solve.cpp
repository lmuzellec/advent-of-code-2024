#include <vector>
#include <regex>
#include <numeric>

#include "utils.hpp"

long solve()
{
  long sum = 0;
  std::vector<std::string> lines = utils::parseInput();
  lines[0].insert(0, "do()");

  std::regex mul_regex1("do\\(\\)(?:(?!don't\\(\\)).)*mul\\((\\d|[1-9]\\d{1,2}),(\\d|[1-9]\\d{1,2})\\)");
  std::regex mul_regex2("mul\\(([1-9]|[1-9]\\d{1,2}),(\\d|[1-9]\\d{1,2})\\)");

  std::string allLines = std::accumulate(lines.begin(), lines.end(), std::string(""));

  auto mul_begin = std::sregex_iterator(allLines.begin(), allLines.end(), mul_regex1);
  auto mul_end = std::sregex_iterator();

  for (std::sregex_iterator i = mul_begin; i != mul_end; ++i)
  {
    std::smatch match = *i;
    std::string complete = match[0].str();

    auto mul_begin2 = std::sregex_iterator(complete.begin(), complete.end(), mul_regex2);
    auto mul_end2 = std::sregex_iterator();
    for (std::sregex_iterator j = mul_begin2; j != mul_end2; ++j)
    {
      std::smatch match2 = *j;

      std::string left = match2[1].str();
      std::string right = match2[2].str();
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