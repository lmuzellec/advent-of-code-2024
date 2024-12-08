#include <vector>
#include <set>
#include <regex>

#include "utils.hpp"

std::vector<std::pair<std::string, std::vector<std::string>>> parseCalibrations(std::vector<std::string> calibrations)
{
  std::vector<std::pair<std::string, std::vector<std::string>>> parsed;

  std::regex target_regex("(\\d+):");
  std::regex member_regex(" (\\d+)");

  for (auto calibration : calibrations)
  {
    auto target_regex_begin = std::sregex_iterator(calibration.begin(), calibration.end(), target_regex);
    auto target_regex_end = std::sregex_iterator();

    auto member_regex_begin = std::sregex_iterator(calibration.begin(), calibration.end(), member_regex);
    auto member_regex_end = std::sregex_iterator();

    std::string target;

    for (std::sregex_iterator i = target_regex_begin; i != target_regex_end; ++i)
    {
      std::smatch target_match = *i;

      target = target_match[1];
    }
    std::vector<std::string> members;

    for (std::sregex_iterator i = member_regex_begin; i != member_regex_end; ++i)
    {
      std::smatch member_match = *i;

      members.push_back(member_match[1]);
    }

    parsed.push_back(std::make_pair(target, members));
  }

  return parsed;
}

bool canBeMadeTrue(long long target, std::vector<std::string> members)
{
  std::set<std::string> optainables = {members[0]};

  for (int i = 1; i < members.size(); i++)
  {
    std::string current = members[i];
    std::set<std::string> newOptainables;

    for (auto optainable : optainables)
    {
      newOptainables.insert(std::to_string(std::stoll(optainable) + std::stoll(current)));
      newOptainables.insert(std::to_string(std::stoll(optainable) * std::stoll(current)));
    }

    optainables = newOptainables;
  }

  return optainables.find(std::to_string(target)) != optainables.end();
}

long long solve()
{
  std::vector<std::string> calibrations = utils::parseInput();

  auto parsedCalibrations = parseCalibrations(calibrations);

  long long result = 0;

  for (auto parsedCalibration : parsedCalibrations)
  {
    long long target = std::stoll(std::get<0>(parsedCalibration));
    if (canBeMadeTrue(target, std::get<1>(parsedCalibration)))
    {
      result += target;
    }
  }

  return result;
}

int main()
{
  long long result = solve();
  std::cout << "result: " << result << std::endl;
}