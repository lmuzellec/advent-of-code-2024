#include <vector>
#include <set>
#include <unordered_map>

#include "utils.hpp"

long solve()
{
  std::vector<std::string> map = utils::parseInput();
  std::vector<std::string> antinodes = std::vector<std::string>(map.size(), std::string(map[0].size(), '.'));

  std::unordered_map<char, std::vector<std::pair<long, long>>> positions;

  for (int y = 0; y < map.size(); y++)
  {
    for (int x = 0; x < map[0].size(); x++)
    {
      char ch = map[y][x];

      if (ch == '.')
      {
        continue;
      }

      if (positions.find(ch) == positions.end())
      {
        positions[ch] = std::vector<std::pair<long, long>>();
      }

      positions[ch].push_back(std::make_pair(x, y));
    }
  }

  for (auto &it : positions)
  {
    char ch = it.first;

    for (int i = 0; i < positions[ch].size(); i++)
    {
      for (int j = 0; j < positions[ch].size(); j++)
      {
        if (i == j)
        {
          continue;
        }

        std::pair<long, long> from = positions[ch][i];
        std::pair<long, long> to = positions[ch][j];

        long fromX = std::get<0>(from);
        long fromY = std::get<1>(from);

        long toX = std::get<0>(to);
        long toY = std::get<1>(to);

        long dX = toX - fromX;
        long dY = toY - fromY;

        long newX = toX;
        long newY = toY;

        int d = 0;

        while (
            newY >= 0 && newY < map.size() &&
            newX >= 0 && newX < map[0].size())
        {
          antinodes[newY][newX] = '#';

          d++;
          newX = toX + dX * d;
          newY = toY + dY * d;
        }
      }
    }
  }

  long result = 0;

  for (int y = 0; y < antinodes.size(); y++)
  {
    for (int x = 0; x < antinodes[0].size(); x++)
    {
      if (antinodes[y][x] == '#')
      {
        result++;
      }
    }
  }

  return result;
}

int main()
{
  long long result = solve();
  std::cout << "result: " << result << std::endl;
}