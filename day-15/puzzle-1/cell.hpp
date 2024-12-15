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
    box,
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