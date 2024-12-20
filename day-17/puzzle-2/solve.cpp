#include <chrono>
#include <vector>
#include <regex>

#include "utils.hpp"
#include "computer.hpp"

inline bool ends_with(std::vector<int> const &value, std::vector<int> const &ending)
{
  if (ending.size() > value.size())
    return false;
  return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}

long solve(std::vector<std::string> input)
{
  int A, B, C;
  std::vector<int> program;

  std::regex register_regex("Register [ABC]: (\\d+)");
  std::regex instructions_regex("Program: (.*)");
  std::regex op_regex("(\\d+)");

  std::smatch matchA;
  std::regex_search(input[0], matchA, register_regex);
  A = std::stoi(matchA[1]);

  std::smatch matchB;
  std::regex_search(input[1], matchB, register_regex);
  B = std::stoi(matchB[1]);

  std::smatch matchC;
  std::regex_search(input[2], matchC, register_regex);
  C = std::stoi(matchC[1]);

  std::smatch matchInstructions;
  std::regex_search(input[4], matchInstructions, instructions_regex);

  std::string instructions = matchInstructions[1];

  auto ops_begin = std::sregex_iterator(instructions.begin(), instructions.end(), op_regex);
  auto ops_end = std::sregex_iterator();

  for (std::sregex_iterator i = ops_begin; i != ops_end; ++i)
  {
    std::smatch op_match = *i;

    program.push_back(std::stoi(op_match[0]));
  }

  // left to right manual dichotomie
  long long fixedA = 07026424356514272;
  // >  35184372088832
  //   247839539763386
  // < 281474976710656
  std::vector<int> out;
  std::vector<int> pend(program.begin(), program.end());

  std::cout << std::oct;

  do
  {
    Computer computer(fixedA, B, C, program);

    computer.run();

    out = computer.getout();

    if (ends_with(out, pend))
    {
      std::cout << fixedA << ": ";
      for (int i = 0; i < out.size(); i++)
      {
        std::cout << out[i];
        if (i < out.size() - 1)
        {
          std::cout << ',';
        }
      }
      std::cout << std::endl;
    }
  } while (program != out);

  return fixedA;
}

int main()
{
  std::vector<std::string> input = utils::parseInput();

  using milli = std::chrono::milliseconds;
  auto start = std::chrono::high_resolution_clock::now();

  long result = solve(input);

  auto finish = std::chrono::high_resolution_clock::now();
  std::cout << "result: " << std::dec << result << std::endl;

  std::cout << "took "
            << std::chrono::duration_cast<milli>(finish - start).count()
            << " ms" << std::endl;
}