#pragma once

#define DEFAULT_COLOR 0x4287f5ff

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

private:
  void clear_board(unsigned c = DEFAULT_COLOR);

  unsigned **_table;
  int _h, _w;
};