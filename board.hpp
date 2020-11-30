#pragma once

#include <thread>
#include "colors.hpp"

class Visualizer;

#define DEFAULT_COLOR Color::Blue

struct coord_t {
  int x, y;
  coord_t(): x(0), y(0) {}
  coord_t(int _x, int _y): x(_x), y(_y) {}
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