#include "cell.hpp"

Cell::Cell()
{
}

Cell::kind Cell::getType()
{
  return type;
}

void Cell::setType(char cell)
{
  switch (cell)
  {
  case '#':
    type = Cell::kind::wall;
    break;
  case '.':
    type = Cell::kind::empty;
    break;
  case 'O':
    type = Cell::kind::box;
    break;
  case '@':
    type = Cell::kind::robot;
    break;
  default:
    break;
  }
}

void Cell::render()
{
  switch (type)
  {
  case Cell::kind::wall:
    std::cout << '#';
    break;
  case Cell::kind::empty:
    std::cout << '.';
    break;
  case Cell::kind::box:
    std::cout << 'O';
    break;
  case Cell::kind::robot:
    std::cout << '@';
    break;
  default:
    break;
  }
}
