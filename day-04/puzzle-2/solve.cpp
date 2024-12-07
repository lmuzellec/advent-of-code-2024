#include <vector>

#include "utils.hpp"

long solve()
{
  long xmas = 0;
  std::vector<std::string> lines = utils::parseInput();

  for (int i = 0; i < lines.size(); i++)
  {
    lines[i].insert(lines[i].begin(), '_');
    lines[i].insert(lines[i].begin(), '_');
    lines[i].insert(lines[i].begin(), '_');
    lines[i].insert(lines[i].begin(), '_');

    lines[i].insert(lines[i].end(), '_');
    lines[i].insert(lines[i].end(), '_');
    lines[i].insert(lines[i].end(), '_');
    lines[i].insert(lines[i].end(), '_');
  }

  lines.insert(lines.begin(), std::string(lines[0].size(), '_'));
  lines.insert(lines.begin(), std::string(lines[0].size(), '_'));
  lines.insert(lines.begin(), std::string(lines[0].size(), '_'));
  lines.insert(lines.begin(), std::string(lines[0].size(), '_'));
  lines.insert(lines.end(), std::string(lines[0].size(), '_'));
  lines.insert(lines.end(), std::string(lines[0].size(), '_'));
  lines.insert(lines.end(), std::string(lines[0].size(), '_'));
  lines.insert(lines.end(), std::string(lines[0].size(), '_'));

  for (int i = 0; i < lines.size(); i++)
  {
    for (int j = 0; j < lines.size(); j++)
    {
      if (lines[i][j] == 'A')
      {
        // M.M
        // .A.
        // S.S
        if (lines[i - 1][j - 1] == 'M' && lines[i - 1][j + 1] == 'M' && lines[i + 1][j - 1] == 'S' && lines[i + 1][j + 1] == 'S')
        {
          xmas++;
        }

        // M.S
        // .A.
        // M.S
        if (lines[i - 1][j - 1] == 'M' && lines[i - 1][j + 1] == 'S' && lines[i + 1][j - 1] == 'M' && lines[i + 1][j + 1] == 'S')
        {
          xmas++;
        }

        // S.S
        // .A.
        // M.M
        if (lines[i - 1][j - 1] == 'S' && lines[i - 1][j + 1] == 'S' && lines[i + 1][j - 1] == 'M' && lines[i + 1][j + 1] == 'M')
        {
          xmas++;
        }

        // S.M
        // .A.
        // S.M
        if (lines[i - 1][j - 1] == 'S' && lines[i - 1][j + 1] == 'M' && lines[i + 1][j - 1] == 'S' && lines[i + 1][j + 1] == 'M')
        {
          xmas++;
        }
      }
    }
  }

  return xmas;
}

int main()
{
  long result = solve();
  std::cout << "result: " << result << std::endl;
}