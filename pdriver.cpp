#include "visualizer.hpp"
#include "board.hpp"

int main() {
  Visualizer::init();
  Board b(6, 8);

  Visualizer v("Path Finding", &b);
  v.run();

  Visualizer::quit();
  return 0;
}