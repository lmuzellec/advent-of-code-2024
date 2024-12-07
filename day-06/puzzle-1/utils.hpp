#pragma once

#include <iostream>
#include <vector>
#include <string>

namespace utils
{
  std::vector<std::string> parseInput();

  std::vector<std::string> split(std::string s, std::string delimiter);
}