#include <vector>
#include <queue>
#include "colors.hpp"
#include "board.hpp"

enum status_t {READY, RUNNING, FINISHED};

class PathFinder {
public:
  PathFinder(Board *b, color_t empty, color_t target, color_t seen, color_t visited, color_t path, int step, int back);
  void operator() (coord_t start, status_t *status);
//private:
  bool is_point_valid(coord_t p);
  void push_adjacent(coord_t pos, std::queue<coord_t> &q, coord_t **prevs);

  Board *_board;
  color_t _empty_color;
  color_t _target_color;
  color_t _seen_color;
  color_t _visited_color;
  color_t _path_color;

  int _sleep_step;
  int _sleep_back;
};