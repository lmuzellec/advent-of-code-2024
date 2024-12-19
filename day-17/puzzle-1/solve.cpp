#include <chrono>
#include <vector>
#include <regex>

#include "utils.hpp"
#include "computer.hpp"

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

  Computer computer(A, B, C, program);

  computer.run();

  std::vector<int> out = computer.getout();

  for (int i = 0; i < out.size(); i++)
  {
    std::cout << out[i];
    if (i < out.size() - 1)
    {
      std::cout << ',';
    }
  }
  std::cout << std::endl;

  long result = 0;
  return result;
}

int main()
{
  std::vector<std::string> input = utils::parseInput();

  using milli = std::chrono::milliseconds;
  auto start = std::chrono::high_resolution_clock::now();

  long result = solve(input);

  auto finish = std::chrono::high_resolution_clock::now();
  std::cout << "result: " << result << std::endl;

  std::cout << "took "
            << std::chrono::duration_cast<milli>(finish - start).count()
            << " ms" << std::endl;
}