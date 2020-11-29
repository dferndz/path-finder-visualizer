#include <random>
#include <string.h>

#include "visualizer.hpp"
#include "colors.hpp"

#define DEFAULT_W 800
#define DEFAULT_H 600
#define LINE_W 4

/*
  Visualizer constructor
    title: char*  - Title of the window
    board: Board* - Pointer to board to render
 */
Visualizer::Visualizer(const char* title, Board *board) {
  // save pointer to board
  _board = board;

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
}

/*
  Destructor
 */
Visualizer::~Visualizer() {
  SDL_DestroyRenderer(_renderer);
  SDL_DestroyWindow(_window);
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
  rect.w = get_window_width() / _board->get_width() - LINE_W;
  rect.h = get_window_height() / _board->get_height() - LINE_W;

  for (unsigned i = 0; i < _board->get_height(); i++) {
    for(unsigned j = 0; j < _board->get_width(); j++) {
      rect.y = i * (rect.h + LINE_W);
      rect.x = j * (rect.w + LINE_W);
      set_sdl_render_color(_renderer, _board->get_table()[i][j]);
      SDL_RenderFillRect(_renderer, &rect);
    }
  }
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
  coord_t coords;

  switch (event.type)
  {
  case SDL_QUIT:
    _is_running = false;
    break;
  
  case SDL_MOUSEBUTTONDOWN:
    SDL_GetMouseState(&m_x, &m_y);
    coords = get_cell(m_x, m_y);
    _board->get_table()[coords.y][coords.x] = Color::Green;
    break;
  
  default:
    break;
  }
}

coord_t Visualizer::get_cell(int m_x, int m_y) {
  coord_t coords;

  int w = get_window_width() / _board->get_width() - LINE_W;
  int h = get_window_height() / _board->get_height() - LINE_W;

  coords.x = m_x / (w + LINE_W);
  coords.y = m_y / (h + LINE_W);

  return coords;
}

void Visualizer::init() {
  SDL_Init(SDL_INIT_VIDEO);
}

void Visualizer::quit() {
  SDL_Quit();
}