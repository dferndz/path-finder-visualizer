#pragma once

#include <thread>
#include "colors.hpp"

class Visualizer;

#define DEFAULT_COLOR Color::Blue

struct coord_t {
  int x, y;
};

class Board {
public:
  Board(int height, int width);
  ~Board();
  unsigned **get_table() { return _table; }
  int get_height() { return _h; }
  int get_width() { return _w; }
  unsigned& get_cell(int x, int y) { return _table[y][x]; }
  void clear_board(unsigned c = DEFAULT_COLOR);
private:
  unsigned **_table;
  int _h, _w;
};