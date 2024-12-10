#include <vector>

#include "utils.hpp"

int firstFreeIndexOfSize(std::vector<std::pair<int, unsigned long long>> disk, int size)
{
  auto it = std::find_if(disk.begin(), disk.end(),
                         [size](std::pair<int, unsigned long long> element)
                         { return std::get<1>(element) == 0 && std ::get<0>(element) >= size; });
  return it - disk.begin();
}

int lastBlockIndex(std::vector<std::pair<int, unsigned long long>> disk, unsigned long long id)
{
  auto result = std::find_if(disk.rbegin(), disk.rend(),
                             [id](std::pair<int, unsigned long long> element)
                             { return std::get<1>(element) == id; });
  return std::distance(result, disk.rend()) - 1;
}

unsigned long long solve()
{
  std::vector<std::string> input = utils::parseInput();

  std::string diskMap = input[0];

  std::vector<std::pair<int, unsigned long long>> disk;

  unsigned long long id = 1;

  for (int c = 0; c < diskMap.size(); c++)
  {
    char ch = diskMap[c];
    int val = ch - '0';

    if (c % 2 == 0)
    {
      disk.push_back(std::make_pair(val, id));

      id++;
    }
    else
    {
      disk.push_back(std::make_pair(val, 0));
    }
  }
  disk.push_back(std::make_pair(20, 0)); // for end safety

  for (unsigned long long i = id - 1; i > 0; i--)
  {
    int blockIndex = lastBlockIndex(disk, i);
    std::pair<int, unsigned long long> block = disk[blockIndex];

    int freeIndexOfSize = firstFreeIndexOfSize(disk, std::get<0>(block));

    if (freeIndexOfSize > blockIndex)
    {
      continue;
    }

    std::pair<int, unsigned long long> freeBlock = disk[freeIndexOfSize];
    int blockSize = std::get<0>(block);
    int freeSize = std::get<0>(freeBlock);

    unsigned long long blockId = std::get<1>(block);

    if (freeSize == blockSize)
    {
      std::swap(disk[freeIndexOfSize], disk[blockIndex]);
    }
    else
    {
      // at blockIndex, replace with empty
      disk[blockIndex].second = 0;
      // std::pair<int, unsigned long long> before = disk[blockIndex - 1];
      // std::pair<int, unsigned long long> after = disk[blockIndex + 1];

      // if (std::get<1>(before) == 0)
      // {
      //   disk[blockIndex].first += std::get<0>(before);
      //   disk[blockIndex - 1].first = 0;
      // }

      // if (std::get<1>(after) == 0)
      // {
      //   disk[blockIndex].first += std::get<0>(after);
      //   disk[blockIndex + 1].first = 0;
      // }

      // at freeindex, replace with block + empty
      disk[freeIndexOfSize].first = blockSize;
      disk[freeIndexOfSize].second = blockId;
      disk.insert(disk.begin() + freeIndexOfSize + 1, std::make_pair(freeSize - blockSize, 0));
    }
  }

  unsigned long long checksum = 0;

  int realIndex = 0;
  for (int i = 0; i < disk.size(); i++)
  {
    int size = std::get<0>(disk[i]);
    unsigned long long val = std::get<1>(disk[i]) - 1;

    for (int s = 0; s < size; s++)
    {
      if (val != ULLONG_MAX)
      {
        checksum += val * realIndex;
      }
      realIndex++;
    }
  }

  return checksum;
}

int main()
{
  unsigned long long result = solve();
  std::cout << "result: " << result << std::endl;
}