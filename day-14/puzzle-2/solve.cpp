#include <chrono>
#include <vector>
#include <regex>

#include "utils.hpp"

int maxX = 101;
int maxY = 103;

inline int positive_modulo(int i, int n)
{
  return (i % n + n) % n;
}

struct Robot
{
  int x, y;
  int vx, vy;
  void move();
};

void Robot::move()
{
  x += vx;
  y += vy;

  x = positive_modulo(x, maxX);
  y = positive_modulo(y, maxY);
}

Robot storobot(std::regex robot_regex, const std::string &line)
{
  auto line_matches = std::sregex_iterator(line.begin(), line.end(), robot_regex);
  std::smatch robot_match = *line_matches;

  Robot robot;
  robot.x = std::stoi(robot_match[1]);
  robot.y = std::stoi(robot_match[2]);
  robot.vx = std::stoi(robot_match[3]);
  robot.vy = std::stoi(robot_match[4]);
  return robot;
}

std::string robotsDisplay(std::vector<Robot> robots)
{
  std::vector<std::vector<int>> display(maxY, std::vector<int>(maxX, 0));

  for (auto &robot : robots)
  {
    display[robot.y][robot.x] += 1;
  }

  std::string finalDisplay = "";

  for (int y = 0; y < display.size(); y++)
  {
    for (int x = 0; x < display[0].size(); x++)
    {
      if (display[y][x] == 0)
      {
        finalDisplay += '.';
      }
      else
      {
        finalDisplay += '#';
      }
    }
    finalDisplay += '\n';
  }

  return finalDisplay;
}

long solve(std::vector<std::string> input)
{
  long result = 0;

  std::vector<Robot> robots(input.size());

  std::regex robot_regex("p=(\\d+),(\\d+) v=(-?\\d+),(-?\\d+)");

  std::transform(input.begin(), input.end(), robots.begin(),
                 [robot_regex](const std::string &line) -> Robot
                 {
                   return storobot(robot_regex, line);
                 });

  int i = 1;

  std::regex line_regex("########");

  while (true)
  {
    for (auto &robot : robots)
    {
      robot.move();
    }

    std::string display = robotsDisplay(robots);

    auto line_matches = std::sregex_iterator(display.begin(), display.end(), line_regex);
    auto line_end = std::sregex_iterator();

    if (line_matches != line_end)
    {
      std::cout << i << std::endl;
      std::cout << display << std::endl;
      std::cin.get();
    }

    i++;
  }

  return result;
}

int main()
{
  std::vector<std::string> input = utils::parseInput();

  using milli = std::chrono::milliseconds;
  auto start = std::chrono::high_resolution_clock::now();

  long long result = solve(input);

  auto finish = std::chrono::high_resolution_clock::now();
  std::cout << "result: " << result << std::endl;

  std::cout << "took "
            << std::chrono::duration_cast<milli>(finish - start).count()
            << " ms" << std::endl;
}