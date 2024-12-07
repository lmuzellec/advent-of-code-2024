#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>

#include "utils.hpp"

bool checkPagesValidity(
    std::unordered_map<std::string, std::vector<std::string>> orderings,
    std::vector<std::string> pages)
{
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

  return validPrint;
}

std::vector<std::string> reorderPages(
    std::unordered_map<std::string, std::vector<std::string>> orderings,
    std::vector<std::string> pages)
{
  if (checkPagesValidity(orderings, pages))
  {
    return pages;
  }

  std::unordered_map<std::string, int> visited;
  bool validPrint = true;

  for (int i = 0; i < pages.size(); i++)
  {
    auto page = pages[i];
    if (orderings.find(page) != orderings.end())
    {
      auto notAllowedBefore = orderings[page];

      for (auto notAllowed : notAllowedBefore)
      {
        auto founded = visited.find(notAllowed);
        if (founded != visited.end())
        {
          std::iter_swap(pages.begin() + founded->second, pages.begin() + i);
          return reorderPages(orderings, pages);
        }
      }
    }

    visited[page] = i;
  }

  return pages;
}

long solve()
{
  std::vector<std::string> lines = utils::parseInput();

  std::unordered_map<std::string, std::vector<std::string>> orderings;

  std::vector<std::__1::string>::iterator it = lines.begin();

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

    bool validPrint = checkPagesValidity(orderings, pages);

    if (validPrint)
    {
      continue;
    }

    auto reordered = reorderPages(orderings, pages);

    auto middleIndex = reordered.size() / 2;

    sum += std::stol(reordered[middleIndex]);
  }

  return sum;
}

int main()
{
  long result = solve();
  std::cout << "result: " << result << std::endl;
}