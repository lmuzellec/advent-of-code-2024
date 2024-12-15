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
  case '[':
    type = Cell::kind::box_left;
    break;
  case ']':
    type = Cell::kind::box_right;
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
  case Cell::kind::box_left:
    std::cout << '[';
    break;
  case Cell::kind::box_right:
    std::cout << ']';
    break;
  case Cell::kind::robot:
    std::cout << '@';
    break;
  default:
    break;
  }
}
