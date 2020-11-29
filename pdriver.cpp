#include "visualizer.hpp"

int main() {
  Visualizer::init();

  Visualizer v("Path Finding");
  v.run();

  Visualizer::quit();
  return 0;
}