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
      if (lines[i][j] == 'X')
      {
        // >
        if (lines[i][j + 1] == 'M' && lines[i][j + 2] == 'A' && lines[i][j + 3] == 'S')
        {
          xmas++;
        }

        // _|
        if (lines[i + 1][j + 1] == 'M' && lines[i + 2][j + 2] == 'A' && lines[i + 3][j + 3] == 'S')
        {
          xmas++;
        }

        // V
        if (lines[i + 1][j] == 'M' && lines[i + 2][j] == 'A' && lines[i + 3][j] == 'S')
        {
          xmas++;
        }

        // |_
        if (lines[i + 1][j - 1] == 'M' && lines[i + 2][j - 2] == 'A' && lines[i + 3][j - 3] == 'S')
        {
          xmas++;
        }

        // <
        if (lines[i][j - 1] == 'M' && lines[i][j - 2] == 'A' && lines[i][j - 3] == 'S')
        {
          xmas++;
        }

        // top <
        if (lines[i - 1][j - 1] == 'M' && lines[i - 2][j - 2] == 'A' && lines[i - 3][j - 3] == 'S')
        {
          xmas++;
        }

        // A
        if (lines[i - 1][j] == 'M' && lines[i - 2][j] == 'A' && lines[i - 3][j] == 'S')
        {
          xmas++;
        }

        // top >
        if (lines[i - 1][j + 1] == 'M' && lines[i - 2][j + 2] == 'A' && lines[i - 3][j + 3] == 'S')
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