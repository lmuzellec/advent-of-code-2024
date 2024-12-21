#include <chrono>
#include <vector>
#include <unordered_map>
#include <regex>

#include "utils.hpp"

bool possible(std::string design, std::vector<std::string> &available)
{
  static std::unordered_map<std::string, bool> memo;

  if (memo.find(design) != memo.end())
  {
    return memo[design];
  }

  if (design.size() == 0)
  {
    memo[design] = true;
    return true;
  }

  for (auto towel : available)
  {
    if (design.starts_with(towel))
    {
      if (possible(design.substr(towel.size()), available))
      {
        memo[design] = true;
        return true;
      }
    }
  }

  memo[design] = false;
  return false;
}

long solve(std::vector<std::string> input)
{
  std::vector<std::string> available;
  std::regex towel_regex("[wubrg]+");

  auto towels_begin = std::sregex_iterator(input[0].begin(), input[0].end(), towel_regex);
  auto towels_end = std::sregex_iterator();

  for (auto it = towels_begin; it != towels_end; it++)
  {
    std::smatch match = *it;
    available.push_back(match[0]);
  }

  std::vector<std::string>
      arrangements(input.begin() + 2, input.end());

  long result = 0;

  for (auto design : arrangements)
  {
    if (possible(design, available))
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