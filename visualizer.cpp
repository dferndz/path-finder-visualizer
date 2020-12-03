#include <random>
#include <string.h>
#include <thread>
#include <queue>
#include <vector>
#include "visualizer.hpp"

static coord_t last_cell;
std::thread t1;

enum status_t {READY, RUNNING, FINISHED};

static status_t finder_status = READY;

static void set_cell(color_t **table, coord_t pos, color_t val) {
  table[pos.y][pos.x] = val;
}

static color_t get_cell(color_t **table, coord_t pos) {
  return table[pos.y][pos.x];
}

static bool is_point_valid(color_t **table, coord_t p, int w, int h) {
  color_t temp;
  if (p.x >= 0 && p.x < w && p.y >= 0 && p.y < h) {
    temp = get_cell(table, p);
    return (temp == TARGET_COLOR || temp == EMPTY_COLOR);
  }
  return false;
}

static void push_adjacent(color_t **table, int w, int h, coord_t pos, std::queue<coord_t> &q, coord_t **prevs) {
  std::vector<coord_t> points = {
    coord_t(pos.x, pos.y-1),
    coord_t(pos.x, pos.y+1),
    coord_t(pos.x-1, pos.y),
    coord_t(pos.x+1, pos.y)
  };

  for (auto p : points) {
    if(is_point_valid(table, p, w, h)) {
      q.push(p);
      prevs[p.y][p.x] = pos;

      if (get_cell(table, p) != TARGET_COLOR)
        set_cell(table, p, Color::LightGreen);
      else
        return;
    }
  }
}

static coord_t** init_p_table(int w, int h) {
  coord_t **ptr = new coord_t*[h];

  for (int i = 0; i < h; i++) {
    ptr[i] = new coord_t[w];
  }

  return ptr;
}

static void free_p_table(coord_t **ptr, int h) {
  for (int i = 0; i < h; i++) {
    delete [] ptr[i];
  }
  delete [] ptr;
}

static void find_path(color_t **table, int w, int h, coord_t start) {
  std::queue<coord_t> q;
  coord_t b;
  coord_t **prev_points = init_p_table(w, h);

  push_adjacent(table, w, h, start, q, prev_points);

  while (!q.empty()) {
    if (get_cell(table, q.front()) == TARGET_COLOR) {
      b = prev_points[q.front().y][q.front().x];

      while (b != start) {
        set_cell(table, b, Color::DarkGreen);
        b = prev_points[b.y][b.x];
        std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_BACK));
      }
      
      free_p_table(prev_points, h);
      finder_status = FINISHED;
      return;
    }
    set_cell(table, q.front(), Color::SoftGreen);
    push_adjacent(table, w, h, q.front(), q, prev_points);
    q.pop();

    std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_STEP));
  }
  free_p_table(prev_points, h);
  finder_status = FINISHED;
}

/*
  Visualizer constructor
    title: char*  - Title of the window
    board: Board* - Pointer to board to render
 */
Visualizer::Visualizer(const char* title, Board *board, int line_width) {
  // save pointer to board
  _board = board;
  _board->clear_board(EMPTY_COLOR);
  _line_w = line_width;

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
  clear_board_button = new Button(_renderer, _font, "Clear", 660, 50);
  set_wall_button = new Button(_renderer, _font, "Set walls", 650, 150, Color::Yellow, 100);
  set_start_cell_button = new Button(_renderer, _font, "Set start", 650, 250, Color::Green, 100);
  set_target_cell_button = new Button(_renderer, _font, "Set target", 650, 350, Color::Red, 100);
  find_path_button = new Button(_renderer, _font, "Find path", 650, 450, Color::Blue, 100);
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
  delete find_path_button;
}

/*
  Run visualizer loop
 */
void Visualizer::run() {
  _is_running = true;
    SDL_Event event;
    while(_is_running) {
        if(finder_status == FINISHED) {
          _selection_status = SET_WALL;
          t1.join();
          finder_status = READY;
        }
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
  rect.w = BOARD_W / _board->get_width() - _line_w;
  rect.h = DEFAULT_H / _board->get_height() - _line_w;

  for (unsigned i = 0; i < _board->get_height(); i++) {
    for(unsigned j = 0; j < _board->get_width(); j++) {
      rect.y = i * (rect.h + _line_w);
      rect.x = j * (rect.w + _line_w);
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
  find_path_button->draw_button(_renderer, _selection_status == FINDING_PATH);
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
    if(_selection_status == FINDING_PATH) break;

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
    if(find_path_button->is_pressed()) {
      if(finder_status == READY) {
         _selection_status = FINDING_PATH;
         t1 = std::thread(find_path, _board->get_table(), _board->get_width(), _board->get_height(), _start);
      }
    }
  case SDL_MOUSEMOTION:
  if(_selection_status == FINDING_PATH) break;

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

  int w = BOARD_W / _board->get_width() - _line_w;
  int h = DEFAULT_H / _board->get_height() - _line_w;

  coords.x = m_x / (w + _line_w);
  coords.y = m_y / (h + _line_w);

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