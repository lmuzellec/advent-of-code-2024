#include <tuple>
#include <vector>
#include <unordered_map>

template <>
struct std::hash<std::pair<int, int>>
{
  std::size_t operator()(const std::pair<int, int> &s) const noexcept
  {
    std::size_t h1 = std::hash<int>{}(s.first);
    std::size_t h2 = std::hash<int>{}(s.second);
    return h1 ^ (h2 << 1);
  }
};

typedef std::pair<int, int> Position;

class Map
{
private:
  std::vector<std::vector<bool>> map;

public:
  Map(std::vector<std::string> input);
  Position start;
  Position end;

  void display();
  bool getAt(Position p) { return map[p.second][p.first]; };
  std::pair<int, int> size() { return {map[0].size(), map.size()}; };

  std::vector<Position> getNeighbors(Position p);

  std::pair<std::unordered_map<Position, int>, std::unordered_map<Position, Position>> dijkstra(Position start);
};