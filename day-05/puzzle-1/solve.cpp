#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>

#include "utils.hpp"

long solve()
{
  std::vector<std::string> lines = utils::parseInput();

  std::unordered_map<std::string, std::vector<std::string>> orderings;

  std::__1::vector<std::__1::string>::iterator it = lines.begin();

  for (; *it != ""; it++)
  {
    auto orders = utils::split(*it, "|");
    std::string first = orders[0];
    std::string then = orders[1];

    if (orderings.find(first) == orderings.end())
    {
      orderings[first] = std::vector<std::string>();
    }
    orderings.at(first).push_back(then);
  }

  it++; // empty line

  long sum = 0;

  for (; it != lines.end(); it++)
  {
    auto pages = utils::split(*it, ",");

    std::unordered_set<std::string> visited;
    bool validPrint = true;

    for (auto page : pages)
    {
      if (orderings.find(page) != orderings.end())
      {
        auto notAllowedBefore = orderings[page];

        for (auto notAllowed : notAllowedBefore)
        {
          if (visited.find(notAllowed) != visited.end())
          {
            validPrint = false;
            break;
          }
        }
      }

      if (!validPrint)
      {
        break;
      }

      visited.insert(page);
    }

    if (!validPrint)
    {
      continue;
    }

    auto middleIndex = pages.size() / 2;

    sum += std::stol(pages[middleIndex]);
  }

  return sum;
}

int main()
{
  long result = solve();
  std::cout << "result: " << result << std::endl;
}