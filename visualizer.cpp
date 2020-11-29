#include <random>
#include <string.h>
#include "visualizer.hpp"
#include "colors.hpp"

#define DEFAULT_W 800
#define DEFAULT_H 600
#define BOARD_W 600
#define LINE_W 2

#define FONT_PD 18

#define FONT_FILE "./assets/Montserrat-font/Montserrat-Bold.ttf"

#define WALL_COLOR Color::Yellow
#define EMPTY_COLOR Color::Blue
#define START_COLOR Color::Green
#define TARGET_COLOR Color::Red

static coord_t last_cell;

/*
  Visualizer constructor
    title: char*  - Title of the window
    board: Board* - Pointer to board to render
 */
Visualizer::Visualizer(const char* title, Board *board) {
  // save pointer to board
  _board = board;
  _board->clear_board(EMPTY_COLOR);

  // create sdl window
  _window = SDL_CreateWindow(
    title, 
    SDL_WINDOWPOS_CENTERED, 
    SDL_WINDOWPOS_CENTERED,
    DEFAULT_W,
    DEFAULT_H,
    SDL_WINDOW_OPENGL
  );

  // create sdl renderer
  _renderer = SDL_CreateRenderer(
    _window,
    -1,
    SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
  );

  // initialize running flag
  _is_running = false;

  // Load Font file
  if(!(_font = TTF_OpenFont(FONT_FILE, FONT_PD))) exit(1);

  // default status
  _selection_status = SET_WALL;
  _start.x = -1;
  _start.y = -1;
  _target.x = -1;
  _target.y = -1;

  // GUI elements
  clear_board_button = new Button(_renderer, _font, "Clear", 660, 5);
  set_start_cell_button = new Button(_renderer, _font, "Set start", 650, 200, Color::Green, 100);
  set_target_cell_button = new Button(_renderer, _font, "Set target", 650, 300, Color::Red, 100);
  set_wall_button = new Button(_renderer, _font, "Set walls", 650, 100, Color::Yellow, 100);
}

bool Visualizer::is_start_set() {
  return (_start.x >= 0 && _start.y >= 0);
}

bool Visualizer::is_target_set() {
  return (_target.x >= 0 && _target.y >= 0);
}

/*
  Destructor
 */
Visualizer::~Visualizer() {
  SDL_DestroyRenderer(_renderer);
  SDL_DestroyWindow(_window);
  TTF_CloseFont(_font);

  delete clear_board_button;
  delete set_start_cell_button;
  delete set_target_cell_button;
  delete set_wall_button;
}

/*
  Run visualizer loop
 */
void Visualizer::run() {
  _is_running = true;
    SDL_Event event;
    while(_is_running) {
        // Process events
        while(SDL_PollEvent(&event)) {
            process_events(event);
        }

        // Clear screen
        set_sdl_render_color(_renderer, Color::White);
        SDL_RenderClear(_renderer);

        // Draw
        draw_controls();
        draw_board();

        // Show what was drawn
        SDL_RenderPresent(_renderer);
    }
}

/*
  Render the board
 */
void Visualizer::draw_board() {
  SDL_Rect rect;
  rect.w = BOARD_W / _board->get_width() - LINE_W;
  rect.h = DEFAULT_H / _board->get_height() - LINE_W;

  for (unsigned i = 0; i < _board->get_height(); i++) {
    for(unsigned j = 0; j < _board->get_width(); j++) {
      rect.y = i * (rect.h + LINE_W);
      rect.x = j * (rect.w + LINE_W);
      set_sdl_render_color(_renderer, _board->get_table()[i][j]);
      SDL_RenderFillRect(_renderer, &rect);
    }
  }
}

void Visualizer::draw_controls() {
  clear_board_button->draw_button(_renderer, false);
  set_start_cell_button->draw_button(_renderer, _selection_status == SET_START);
  set_target_cell_button->draw_button(_renderer, _selection_status == SET_TARGET);
  set_wall_button->draw_button(_renderer, _selection_status == SET_WALL);
}

int Visualizer::get_window_height() {
  int w, h;
  SDL_GetWindowSize(_window, &w, &h);
  return h;
}

int Visualizer::get_window_width() {
  int w, h;
  SDL_GetWindowSize(_window, &w, &h);
  return w;
}

/*
  Process sdl events
 */
void Visualizer::process_events(SDL_Event &event) {
  int m_x, m_y;
  int mouse_status;
  coord_t coords;

  switch (event.type)
  {
  case SDL_QUIT:
    _is_running = false;
    break;
  
  case SDL_MOUSEBUTTONDOWN:
    if(clear_board_button->is_pressed()) {
      _board->clear_board(EMPTY_COLOR);
      _start.x = -1;
      _start.y = -1;
      _target.x = -1;
      _target.y = -1;
      break;
    }
    if(set_start_cell_button->is_pressed()) {
      _selection_status = SET_START;
      break;
    }
    if(set_target_cell_button->is_pressed()) {
      _selection_status = SET_TARGET;
      break;
    }
    if(set_wall_button->is_pressed()) {
      _selection_status = SET_WALL;
      break;
    }
  case SDL_MOUSEMOTION:
    mouse_status = SDL_GetMouseState(&m_x, &m_y);
    coords = get_cell(m_x, m_y);

    if (
      m_x <= BOARD_W &&
      mouse_status & SDL_BUTTON(1) && 
      (event.type == SDL_MOUSEMOTION && (coords.x != last_cell.x || coords.y != last_cell.y)) 
      || event.type == SDL_MOUSEBUTTONDOWN
    ) {

      if(_selection_status == SET_WALL) {
        _board->get_cell(coords.x, coords.y) == WALL_COLOR ?
        _board->get_cell(coords.x, coords.y) = EMPTY_COLOR :
        _board->get_cell(coords.x, coords.y) = WALL_COLOR;
      }

      if(_selection_status == SET_START) {
        if(is_start_set()) {
          _board->get_cell(_start.x, _start.y) = EMPTY_COLOR;
        }
        _start.x = coords.x;
        _start.y = coords.y;

        _board->get_cell(_start.x, _start.y) = START_COLOR;
      }

      if(_selection_status == SET_TARGET) {
        if(is_target_set()) {
          _board->get_cell(_target.x, _target.y) = EMPTY_COLOR;
        }
        _target.x = coords.x;
        _target.y = coords.y;

        _board->get_cell(_target.x, _target.y) = TARGET_COLOR;
      }
      

      last_cell = coords;

    }
    break;
  
  default:
    break;
  }
}

coord_t Visualizer::get_cell(int m_x, int m_y) {
  coord_t coords;

  int w = BOARD_W / _board->get_width() - LINE_W;
  int h = DEFAULT_H / _board->get_height() - LINE_W;

  coords.x = m_x / (w + LINE_W);
  coords.y = m_y / (h + LINE_W);

  return coords;
}

void Visualizer::init() {
  SDL_Init(SDL_INIT_VIDEO);
  TTF_Init();
}

void Visualizer::quit() {
  SDL_Quit();
  TTF_Quit();
}