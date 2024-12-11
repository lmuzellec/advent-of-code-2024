#include <vector>
#include <string>
#include <regex>

#include "utils.hpp"

std::vector<unsigned long long> blink(std::vector<unsigned long long> arrangement)
{
  std::vector<unsigned long long> result;

  for (auto rock : arrangement)
  {
    if (rock == 0)
    {
      result.push_back(1);
    }
    else if (std::to_string(rock).size() % 2 == 0)
    {
      std::string srock = std::to_string(rock);
      result.push_back(std::stoull(srock.substr(0, srock.size() / 2)));
      result.push_back(std::stoull(srock.substr(srock.size() / 2)));
    }
    else
    {
      result.push_back(rock * 2024);
    }
  }

  return result;
}

unsigned long long solve()
{
  std::string input;
  std::getline(std::cin, input);

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

  for (int i = 0; i < 25; i++)
  {
    arrangement = blink(arrangement);
  }

  return arrangement.size();
}

int main()
{
  unsigned long long result = solve();
  std::cout << "result: " << result << std::endl;
}