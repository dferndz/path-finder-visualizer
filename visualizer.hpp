#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "board.hpp"
#include "button.hpp"
#include "colors.hpp"

#define SET_WALL 0x1
#define SET_START 0x2
#define SET_TARGET 0x4
#define FINDING_PATH 0x8

#define DEFAULT_W 800
#define DEFAULT_H 600
#define BOARD_W 600

#define LINE_W 1

#define FONT_PD 200
#define FONT_FILE "./assets/Montserrat-font/Montserrat-Bold.ttf"

#define WALL_COLOR Color::Yellow
#define EMPTY_COLOR Color::Blue
#define START_COLOR Color::Green
#define TARGET_COLOR Color::Red

#define SLEEP_STEP 5
#define SLEEP_BACK 30

class Visualizer {
public:
  static void init();
  static void quit();

  Visualizer(const char *, Board *b, int line_width = LINE_W);
  ~Visualizer();
  void run();
  bool is_running() { return _is_running; }

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

  // Options
  int _line_w;

  // Gui elements
  Button *clear_board_button;
  Button *set_start_cell_button;
  Button *set_target_cell_button;
  Button *set_wall_button;
  Button *find_path_button;
};