#pragma once

#include <vector>
#include <string>
#include <iostream>

#include "cell.hpp"

class Map
{
private:
  std::vector<std::vector<Cell>> cells;
  std::pair<int, int> robot;

public:
  Map(std::vector<std::string>);
  std::vector<std::vector<Cell>> getCells();
  void render();
  Cell getCell(std::pair<int, int>);
  void move(char);
};