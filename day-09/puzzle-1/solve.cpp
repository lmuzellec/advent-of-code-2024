#include <vector>

#include "utils.hpp"

std::vector<unsigned long long> repeat(int val, unsigned long long id)
{
  return std::vector<unsigned long long>(val, id);
}

int firstFreeIndex(std::vector<unsigned long long> disk)
{
  auto it = std::find(disk.begin(), disk.end(), 0);
  return it - disk.begin();
}

int lastBlockIndex(std::vector<unsigned long long> disk)
{
  auto result = std::find_if(disk.rbegin(), disk.rend(),
                             [](unsigned long long i)
                             { return i != 0; });
  return std::distance(result, disk.rend()) - 1;
}

unsigned long long solve()
{
  std::vector<std::string> input = utils::parseInput();

  std::string diskMap = input[0];

  std::vector<unsigned long long> disk;

  unsigned long long id = 1;

  for (int c = 0; c < diskMap.size(); c++)
  {
    char ch = diskMap[c];
    int val = ch - '0';

    if (c % 2 == 0)
    {
      std::vector<unsigned long long> ids = repeat(val, id);
      disk.insert(disk.end(), ids.begin(), ids.end());

      id++;
    }
    else
    {
      std::vector<unsigned long long> frees = repeat(val, 0);
      disk.insert(disk.end(), frees.begin(), frees.end());
    }
  }

  int freeIndex = firstFreeIndex(disk);
  int blockIndex = lastBlockIndex(disk);

  while (freeIndex < blockIndex)
  {
    std::swap(disk[freeIndex], disk[blockIndex]);

    freeIndex = firstFreeIndex(disk);
    blockIndex = lastBlockIndex(disk);
  }

  unsigned long long checksum = 0;

  for (int i = 0; i < disk.size(); i++)
  {
    unsigned long long id = disk[i];
    if (id == 0)
    {
      break;
    }

    unsigned long long val = id - 1;
    checksum += val * i;
  }

  return checksum;
}

int main()
{
  unsigned long long result = solve();
  std::cout << "result: " << result << std::endl;
}