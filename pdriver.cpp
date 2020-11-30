#include "visualizer.hpp"
#include "board.hpp"

int main() {
  Visualizer::init();
  Board b(30, 30);

  Visualizer *v = new Visualizer("Path Finding", &b);
  v->run();

  delete v;
  Visualizer::quit();
  return 0;
}