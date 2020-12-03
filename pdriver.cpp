#include <unistd.h>
#include <string.h>
#include <iostream>
#include "visualizer.hpp"
#include "board.hpp"

#define DEFAULT_GRID_W 30
#define DEFAULT_GRID_H 30
#define DEFAULT_LINE_W 1

class Program {
public:
  Program(int argc = 0, char *argv[] = nullptr): _grid_w(DEFAULT_GRID_W), _grid_h(DEFAULT_GRID_H), _line_w(DEFAULT_LINE_W) {
    Visualizer::init();
    parse_options(argc, argv);
    _board = new Board(_grid_h, _grid_w);
    _visualizer = new Visualizer("Path Finding", _board, _line_w);
  }
  ~Program() {
    delete _board;
    delete _visualizer;
    Visualizer::quit();
  }

  void run() {
    _visualizer->run();
  }

private:
  void parse_options(int argc, char *argv[]) {
    int c;

    while ((c = getopt(argc, argv, "hx:y:l:")) != -1) {
      switch(c) {
        case 'h':
          // usage
          print_usage();
          break;
        case 'x':
          // set width
          _grid_w = atoi(optarg);
          break;
        case 'y':
          // set height
          _grid_h = atoi(optarg);
          break;
        case 'l':
          //set line width
          _line_w = atoi(optarg);
          break;
        default:
          exit(0);
          break;
      }
    }

  }

  static void print_usage() {
    std::cout << "Usage: pdriver [-h] [-x number] [-y number] [-l number]" << std::endl;
    std::cout << " h   Prints this message" << std::endl;
    std::cout << " x   Set width of canvas" << std::endl;
    std::cout << " y   Set height of canvas" << std::endl;
    std::cout << " l   Set canvas lines width" << std::endl;
    exit(0);
  }

  Board *_board;
  Visualizer *_visualizer;

  int _grid_w, _grid_h;
  int _line_w;
};

int main(int argc, char *argv[]) {
  Program p(argc, argv);
  p.run();
  return 0;
}