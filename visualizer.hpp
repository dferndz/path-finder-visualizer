#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "board.hpp"
#include "button.hpp"

#define SET_WALL 0x1
#define SET_START 0x2
#define SET_TARGET 0x4
#define FINDING_PATH 0x8

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
  void draw_controls();

  void process_events(SDL_Event&);
  coord_t get_cell(int, int);

  SDL_Window *_window;
  SDL_Renderer *_renderer;
  TTF_Font *_font;
  bool _is_running;
  Board *_board;

  bool is_start_set();
  bool is_target_set();

  unsigned _selection_status;

  coord_t _start;
  coord_t _target;

  // Gui elements
  Button *clear_board_button;
  Button *set_start_cell_button;
  Button *set_target_cell_button;
  Button *set_wall_button;
  Button *find_path_button;
};