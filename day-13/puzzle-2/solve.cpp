#include <chrono>
#include <vector>
#include <regex>

#include "utils.hpp"

struct Equation
{
  long double a = 0;
  long double b = 0;
  long double c = 0;
  long double d = 0;
  long double e = 0;
  long double f = 0;
};

std::vector<Equation> parseEquation(std::vector<std::string> input)
{
  std::vector<Equation> equations;

  auto it = input.begin();

  std::regex button_regex("Button [AB]: X\\+(\\d+), Y\\+(\\d+)");
  std::regex prize("Prize: X=(\\d+), Y=(\\d+)");

  while (it != input.end())
  {
    Equation equation;

    std::string buttonALine = *it;
    auto button_a_begin = std::sregex_iterator(buttonALine.begin(), buttonALine.end(), button_regex);
    std::smatch matchA = *button_a_begin;

    equation.a = std::stoull(matchA[1].str());
    equation.c = std::stoull(matchA[2].str());

    it++;
    std::string buttonBLine = *it;
    auto button_b_begin = std::sregex_iterator(buttonBLine.begin(), buttonBLine.end(), button_regex);
    std::smatch matchB = *button_b_begin;

    equation.b = std::stoull(matchB[1].str());
    equation.d = std::stoull(matchB[2].str());

    it++;
    std::string prizeLine = *it;
    auto prize_begin = std::sregex_iterator(prizeLine.begin(), prizeLine.end(), prize);
    std::smatch prize = *prize_begin;

    equation.e = std::stoull(prize[1].str()) + 10000000000000;
    equation.f = std::stoull(prize[2].str()) + 10000000000000;

    equations.push_back(equation);

    it++;
    if (it != input.end())
    {
      it++;
    }
  }

  return equations;
}

long double solve(long double a,
                  long double b,
                  long double c,
                  long double d,
                  long double e,
                  long double f)
{
  long double determinant = a * d - b * c;
  long double xNumDeterminant = e * d - b * f;
  long double yNumDeterminant = a * f - e * c;

  // One solution
  if (determinant != 0)
  {
    long double x = xNumDeterminant / determinant;
    long double y = yNumDeterminant / determinant;

    long double intpartx;
    long double intparty;

    if (std::modf(x, &intpartx) == 0.0 && std::modf(y, &intparty) == 0.0)
    {
      return x * 3 + y;
    }
    return -1;
  }
  // infinite solutions
  else if (xNumDeterminant == 0 && yNumDeterminant == 0)
  {
    return -1;
  }
  // no solutions
  else
  {
    return -1;
  }
}

long double solve(std::vector<std::string> input)
{
  long double result = 0;

  std::vector<Equation> equations = parseEquation(input);

  for (auto equation : equations)
  {
    long double equationResult = solve(equation.a, equation.b, equation.c, equation.d, equation.e, equation.f);

    if (equationResult != -1)
    {
      result += equationResult;
    }
  }

  return result;
}

int main()
{
  std::vector<std::string> input = utils::parseInput();

  using milli = std::chrono::milliseconds;
  auto start = std::chrono::high_resolution_clock::now();

  long double result = solve(input);

  auto finish = std::chrono::high_resolution_clock::now();
  std::cout << "result: " << std::format("{}", result) << std::endl;

  std::cout << "took "
            << std::chrono::duration_cast<milli>(finish - start).count()
            << " ms" << std::endl;
}