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

void displayRobots(std::vector<Robot> robots)
{
  std::vector<std::vector<int>> display(maxY, std::vector<int>(maxX, 0));

  for (auto &robot : robots)
  {
    display[robot.y][robot.x] += 1;
  }

  for (int y = 0; y < display.size(); y++)
  {
    for (int x = 0; x < display[0].size(); x++)
    {
      if (display[y][x] == 0)
      {
        std::cout << '.';
      }
      else
      {
        std::cout << std::to_string(display[y][x]);
      }
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
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

  for (int i = 0; i < 100; i++)
  {
    for (auto &robot : robots)
    {
      robot.move();
    }
    std::cout << std::endl
              << i + 1 << std::endl;
    displayRobots(robots);
  }

  int topLeft = 0;
  int topRight = 0;
  int bottomLeft = 0;
  int bottomRight = 0;

  int halfX = maxX / 2;
  int halfY = maxY / 2;

  for (auto &robot : robots)
  {
    if (robot.x < halfX &&
        robot.y < halfY)
    {
      topLeft++;
    }

    if (robot.x > halfX &&
        robot.y < halfY)
    {
      topRight++;
    }

    if (robot.x < halfX &&
        robot.y > halfY)
    {
      bottomLeft++;
    }

    if (robot.x > halfX &&
        robot.y > halfY)
    {
      bottomRight++;
    }
  }

  return topLeft * topRight * bottomLeft * bottomRight;
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