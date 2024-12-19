#include "computer.hpp"

#include <stdexcept>
#include <cmath>

int Computer::take()
{
  return program[index];
}

void Computer::next()
{
  index++;
}

int Computer::combo(int operand)
{
  switch (operand)
  {
  case 0:
  case 1:
  case 2:
  case 3:
    return operand;
  case 4:
    return A;
  case 5:
    return B;
  case 6:
    return C;
  default:
    throw std::invalid_argument("unknown operand :" + std::to_string(operand));
  }
}

int Computer::literal(int operand)
{
  int value;
  std::memcpy(&value, &operand, sizeof(decltype(value)));
  return value;
}

void Computer::adv(int operand)
{
  int c = combo(operand);

  A = A / pow(2, c);
}

void Computer::bxl(int operand)
{
  int l = literal(operand);

  B = B ^ l;
}

void Computer::bst(int operand)
{
  int c = combo(operand);

  B = c % 8;
}

void Computer::jnz(int operand)
{
  if (A == 0)
  {
    return;
  }

  int l = literal(operand);

  index = l;
}

void Computer::bxc(int operand)
{
  B = B ^ C;
}

void Computer::out(int operand)
{
  int c = combo(operand);

  output.push_back(c % 8);
}

void Computer::bdv(int operand)
{
  int c = combo(operand);

  B = A / pow(2, c);
}

void Computer::cdv(int operand)
{
  int c = combo(operand);

  C = A / pow(2, c);
}

void Computer::run()
{
  while (index < program.size())
  {
    int instruction = take();
    next();

    int operand = take();
    next();

    switch (instruction)
    {
    case 0:
      adv(operand);
      break;
    case 1:
      bxl(operand);
      break;
    case 2:
      bst(operand);
      break;
    case 3:
      jnz(operand);
      break;
    case 4:
      bxc(operand);
      break;
    case 5:
      out(operand);
      break;
    case 6:
      bdv(operand);
      break;
    case 7:
      cdv(operand);
      break;
    default:
      throw std::invalid_argument("unknown instruction :" + std::to_string(instruction));
    }
  }
}