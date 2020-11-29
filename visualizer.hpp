#pragma once

#include <SDL2/SDL.h>
#include "board.hpp"

class Visualizer {
public:
  static void init();
  static void quit();
  Visualizer(const char *, Board *b);
  ~Visualizer();
  void run();
  bool is_running() { return _is_running; }
  int get_window_width();
  int get_window_height();
private:
  void draw_board();
  void process_events(SDL_Event&);
  coord_t get_cell(int, int);

  SDL_Window *_window;
  SDL_Renderer *_renderer;
  bool _is_running;
  Board *_board;
};