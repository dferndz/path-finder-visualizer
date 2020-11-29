#include "board.hpp"
#include "visualizer.hpp"

Board::Board(int height, int width): _h(height), _w(width) {
  _table = new unsigned*[_h];

  for (unsigned i = 0; i < _h; i++) {
    _table[i] = new unsigned[_w];
  }

  clear_board();
}

Board::~Board() {
  for (unsigned i = 0; i < _h; i++) {
    delete [] _table[i];
  }
  delete [] _table;
}

void Board::clear_board(unsigned c) {
  for(unsigned i = 0; i < _h; i++) {
    for(unsigned j = 0; j < _w; j++) {
      _table[i][j] = c;
    }
  }
}