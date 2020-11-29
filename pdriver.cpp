#include "visualizer.hpp"
#include "board.hpp"

int main() {
  Visualizer::init();
  Board b(20, 20);

  Visualizer *v = new Visualizer("Path Finding", &b);
  v->run();

  delete v;
  Visualizer::quit();
  return 0;
}