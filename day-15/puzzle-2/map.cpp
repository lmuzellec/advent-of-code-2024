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
    for (int x = 0; x < lines[0].size(); x++)
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
  switch (movement)
  {
  case '<':
  case '>':
  {
    std::pair<int, int> next = robot;
    Cell::kind nextType;

    do
    {
      next = next + std::make_pair(dX[movement], dY[movement]);
      nextType = getCell(next).getType();
    } while (nextType == Cell::kind::box_left || nextType == Cell::kind::box_right);

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
    break;
  }
  case '^':
  case 'v':
  {
    bool canMove = canPush(movement, robot + std::make_pair(dX[movement], dY[movement]));

    if (!canMove)
    {
      return;
    }

    push(movement, robot + std::make_pair(dX[movement], dY[movement]));
    robot = robot + std::make_pair(dX[movement], dY[movement]);
  }
  }
}

bool Map::canPush(char movement, std::pair<int, int> position)
{
  switch (getCell(position).getType())
  {
  case Cell::kind::wall:
    return false;
  case Cell::kind::robot:
  case Cell::kind::empty:
    return true;
  case Cell::kind::box_left:
    return canPush(movement, position + std::make_pair(0, dY[movement])) &&
           canPush(movement, position + std::make_pair(1, dY[movement]));
  case Cell::kind::box_right:
    return canPush(movement, position + std::make_pair(0, dY[movement])) &&
           canPush(movement, position + std::make_pair(-1, dY[movement]));
  }
}

void Map::push(char movement, std::pair<int, int> position)
{
  Cell::kind type = getCell(position).getType();
  if (type == Cell::kind::box_left)
  {
    push(movement, position + std::make_pair(0, dY[movement]));
    push(movement, position + std::make_pair(1, dY[movement]));
  }
  else if (type == Cell::kind::box_right)
  {
    push(movement, position + std::make_pair(0, dY[movement]));
    push(movement, position + std::make_pair(-1, dY[movement]));
  }

  std::pair<int, int> to = position;
  std::pair<int, int> from = to - std::make_pair(dX[movement], dY[movement]);
  std::swap(cells[to.second][to.first], cells[from.second][from.first]);
}
