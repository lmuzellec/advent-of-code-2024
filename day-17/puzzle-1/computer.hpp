#pragma once

#include <vector>

class Computer
{
private:
  int A, B, C, index;

  std::vector<int> program;
  std::vector<int> output;

  int take();
  void next();

  int combo(int);
  int literal(int);

  void adv(int);
  void bxl(int);
  void bst(int);
  void jnz(int);
  void bxc(int);
  void out(int);
  void bdv(int);
  void cdv(int);

public:
  Computer(int a, int b, int c, std::vector<int> p) : A(a), B(b), C(c), index(0), program(p) {};
  void run();

  std::vector<int> getout() { return output; };
};