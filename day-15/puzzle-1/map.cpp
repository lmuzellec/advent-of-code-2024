#include <map>

#include "map.hpp"
#include "cell.hpp"

std::map<char, int> dX({{'^', 0}, {'>', 1}, {'v', 0}, {'<', -1}});
std::map<char, int> dY({{'^', -1}, {'>', 0}, {'v', 1}, {'<', 0}});

std::pair<int, int> operator+(const std::pair<int, int> &l, const std::pair<int, int> &r)
{
  return {l.first + r.first, l.second + r.second};
}

std::pair<int, int> operator-(const std::pair<int, int> &l, const std::pair<int, int> &r)
{
  return {l.first - r.first, l.second - r.second};
}

Map::Map(std::vector<std::string> lines)
{
  std::vector<std::vector<Cell>> cellsR(lines.size(), std::vector<Cell>(lines[0].size()));

  for (int y = 0; y < lines.size(); y++)
  {
    for (int x = 0; x < lines.size(); x++)
    {
      Cell cell;
      cell.setType(lines[y][x]);

      if (cell.getType() == Cell::kind::robot)
      {
        robot = std::make_pair(x, y);
      }

      cellsR[y][x] = cell;
    }
  }

  cells = cellsR;
}

void Map::render()
{
  for (auto line : cells)
  {
    for (auto cell : line)
    {
      cell.render();
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

std::vector<std::vector<Cell>> Map::getCells()
{
  return cells;
}

Cell Map::getCell(std::pair<int, int> position)
{
  return cells[position.second][position.first];
}

void Map::move(char movement)
{
  std::pair<int, int> next = robot;
  Cell::kind nextType;

  do
  {
    next = next + std::make_pair(dX[movement], dY[movement]);
    nextType = getCell(next).getType();
  } while (nextType == Cell::kind::box);

  if (nextType == Cell::kind::wall)
  {
    return;
  }

  Cell::kind toType;
  do
  {
    std::pair<int, int> to = next;
    std::pair<int, int> from = next - std::make_pair(dX[movement], dY[movement]);
    std::swap(cells[to.second][to.first], cells[from.second][from.first]);

    next = from;
    toType = getCell(to).getType();
  } while (toType != Cell::kind::robot);
  robot = robot + std::make_pair(dX[movement], dY[movement]);
}