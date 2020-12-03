#include "path.hpp"
#include <thread>

PathFinder::PathFinder(Board *b, color_t empty, color_t target, color_t seen, color_t visited, color_t path, int step, int back) {
  _board = b;
  _empty_color = empty;
  _target_color = target;
  _seen_color = seen;
  _visited_color = visited;
  _sleep_step = step;
  _sleep_back = back;
  _path_color= path;
}

static void set_cell(color_t **table, coord_t pos, color_t val) {
  table[pos.y][pos.x] = val;
}

static color_t get_cell(color_t **table, coord_t pos) {
  return table[pos.y][pos.x];
}

bool PathFinder::is_point_valid(coord_t p) {
  color_t temp;
  if (p.x >= 0 && p.x < _board->get_width() && p.y >= 0 && p.y < _board->get_height()) {
    temp = get_cell(_board->get_table(), p);
    return (temp == _target_color || temp == _empty_color);
  }
  return false;
}

void PathFinder::push_adjacent(coord_t pos, std::queue<coord_t> &q, coord_t **prevs) {
  std::vector<coord_t> points = {
    coord_t(pos.x, pos.y-1),
    coord_t(pos.x, pos.y+1),
    coord_t(pos.x-1, pos.y),
    coord_t(pos.x+1, pos.y)
  };

  for (auto p : points) {
    if(is_point_valid(p)) {
      q.push(p);
      prevs[p.y][p.x] = pos;

      if (get_cell(_board->get_table(), p) != _target_color)
        set_cell(_board->get_table(), p, _seen_color);
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

void PathFinder::operator() (coord_t start, status_t *status) {
  int w = _board->get_width(), h = _board->get_height();
  color_t **table = _board->get_table();
  coord_t b;
  std::queue<coord_t> q;
  coord_t **prev_points = init_p_table(w, h);

  *status = RUNNING;

  push_adjacent(start, q, prev_points);

  while (!q.empty()) {
    if (get_cell(table, q.front()) == _target_color) {
      b = prev_points[q.front().y][q.front().x];

      while (b != start) {
        set_cell(table, b, _path_color);
        b = prev_points[b.y][b.x];
        std::this_thread::sleep_for(std::chrono::milliseconds(_sleep_back));
      }
      
      free_p_table(prev_points, h);
      *status = FINISHED;
      return;
    }
    set_cell(table, q.front(), _visited_color);
    push_adjacent(q.front(), q, prev_points);
    q.pop();

    std::this_thread::sleep_for(std::chrono::milliseconds(_sleep_step));
  }

  free_p_table(prev_points, h);
  *status = FINISHED;
}