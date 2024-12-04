#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <execution>

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

bool validReport(std::vector<long> report)
{
  long first = report[0];
  long second = report[1];

  if (first == second)
  {
    return false;
  }

  if (first > second)
  {
    std::reverse(report.begin(), report.end());
  }

  for (int i = 0; i < report.size() - 1; i++)
  {
    long first = report[i];
    long second = report[i + 1];

    long delta = second - first;
    if (delta > 3 || delta <= 0)
    {
      return false;
    }
  }

  return true;
}

long solve()
{
  long validReports = 0;
  std::vector<std::string> lines = parseInput();

  std::vector<std::vector<long>> reports;

  for (auto line : lines)
  {
    auto report = split(line, " ");
    std::vector<long> reportLong(report.size());

    std::transform(report.begin(), report.end(), reportLong.begin(), [](std::string x)
                   { return std::stol(x); });

    reports.push_back(reportLong);
  }

  for (auto report : reports)
  {
    std::vector<std::vector<long>> alternativeReports;
    alternativeReports.push_back(report);

    if (validReport(report))
    {
      validReports++;
      continue;
    }

    bool valid = false;

    for (int i = 0; i < report.size(); i++)
    {
      std::vector<long> copy(report.begin(), report.end());
      copy.erase(copy.begin() + i);

      if (validReport(copy))
      {
        valid = true;
        break;
      }
    }

    if (valid)
    {
      validReports++;
    }
  }

  return validReports;
}

int main()
{
  long result = solve();
  std::cout << "result: " << result << std::endl;
}