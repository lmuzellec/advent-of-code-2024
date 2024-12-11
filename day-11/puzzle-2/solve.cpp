#include <vector>
#include <deque>
#include <string>
#include <regex>
#include <unordered_map>
#include <chrono>

#include "utils.hpp"

namespace std
{
  template <>
  struct hash<std::vector<unsigned long long>>
  {
    std::size_t operator()(const std::vector<unsigned long long> &vec) const
    {
      std::size_t seed = vec.size();
      for (auto &i : vec)
      {
        seed ^= i + 0x9e3779b9 + (seed << 6) + (seed >> 2);
      }
      return seed;
    }
  };

  // Custom hash function for std::pair<std::vector<unsigned long long>, int>
  template <>
  struct hash<std::pair<std::vector<unsigned long long>, int>>
  {
    std::size_t operator()(const std::pair<std::vector<unsigned long long>, int> &p) const
    {
      std::size_t seed = hash<std::vector<unsigned long long>>()(p.first);
      seed ^= hash<int>()(p.second) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
      return seed;
    }
  };
}

unsigned long long blink(std::vector<unsigned long long> arrangement, int depth)
{
  static std::unordered_map<std::pair<std::vector<unsigned long long>, int>, unsigned long long> memo;

  std::pair<std::vector<unsigned long long>, int> args = std::make_pair(arrangement, depth);
  if (memo.find(args) != memo.end())
  {
    return memo[args];
  }

  if (depth == 0)
  {
    memo[args] = arrangement.size();
    return arrangement.size();
  }

  unsigned long long result = 0;

  for (auto rock : arrangement)
  {
    if (rock == 0)
    {
      result += blink({1}, depth - 1);
    }
    else if (std::to_string(rock).size() % 2 == 0)
    {
      std::string srock = std::to_string(rock);
      result += blink({std::stoull(srock.substr(0, srock.size() / 2)),
                       std::stoull(srock.substr(srock.size() / 2))},
                      depth - 1);
    }
    else
    {
      result += blink({rock * 2024}, depth - 1);
    }
  }

  memo[args] = result;
  return result;
}

unsigned long long solve()
{
  std::string input;
  std::getline(std::cin, input);

  using milli = std::chrono::milliseconds;
  auto start = std::chrono::high_resolution_clock::now();

  std::vector<unsigned long long> arrangement;

  std::regex number("\\d+");

  auto numbers_begin = std::sregex_iterator(input.begin(), input.end(), number);
  auto numbers_end = std::sregex_iterator();

  for (std::sregex_iterator i = numbers_begin; i != numbers_end; i++)
  {
    std::smatch match = *i;
    std::string complete = match[0].str();

    arrangement.push_back(std::stoull(complete));
  }

  unsigned long long size = blink(arrangement, 75);

  auto finish = std::chrono::high_resolution_clock::now();
  std::cout << "took "
            << std::chrono::duration_cast<milli>(finish - start).count()
            << " ms" << std::endl;

  return size;
}

int main()
{
  unsigned long long result = solve();
  std::cout << "result: " << result << std::endl;
}