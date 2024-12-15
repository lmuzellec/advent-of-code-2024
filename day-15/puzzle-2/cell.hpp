#pragma once
#include <utility>
#include <iostream>

class Cell
{
public:
  enum kind
  {
    empty,
    wall,
    box_left,
    box_right,
    robot
  };

private:
  kind type;

public:
  Cell();
  kind getType();
  void setType(char);
  void render();
};