#include <unistd.h>
#include <string.h>
#include <iostream>
#include "visualizer.hpp"
#include "board.hpp"

#define DEFAULT_GRID_W 30
#define DEFAULT_GRID_H 30

class Program {
public:
  Program(int argc = 0, char *argv[] = nullptr): _grid_w(DEFAULT_GRID_W), _grid_h(DEFAULT_GRID_H), _options(DEFAULT_OPTIONS) {
    Visualizer::init();

    parse_options(argc, argv);

    _board = new Board(_grid_h, _grid_w);
    _visualizer = new Visualizer("Path Finding", _board, _options);
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
  static color_t rgb_to_rgba(unsigned rgb) {
    return ((rgb << 8) | 0xff);
  }

  void parse_options(int argc, char *argv[]) {
    int c;
    unsigned temp_color;

    while ((c = getopt(argc, argv, "hdx:y:l:S:B:e:t:s:w:v:c:p:")) != -1) {
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
          _options.line_w = atoi(optarg);
          break;
        case 'S':
          _options.sleep_step = atoi(optarg);
          break;
        case 'd':
          _options.diagonal_paths = true;
          break;
        case 'B':
          _options.sleep_back = atoi(optarg);
          break;
        case 'e':
          sscanf(optarg, "%x", &temp_color);
          _options.empty_color = rgb_to_rgba(temp_color);
          break;
        case 't':
          sscanf(optarg, "%x", &temp_color);
          _options.target_color = rgb_to_rgba(temp_color);
          break;
        case 's':
          sscanf(optarg, "%x", &temp_color);
          _options.start_color = rgb_to_rgba(temp_color);
          break;
        case 'w':
          sscanf(optarg, "%x", &temp_color);
          _options.wall_color = rgb_to_rgba(temp_color);
          break;
        case 'v':
          sscanf(optarg, "%x", &temp_color);
          _options.visited_color = rgb_to_rgba(temp_color);
          break;
        case 'c':
          sscanf(optarg, "%x", &temp_color);
          _options.seen_color = rgb_to_rgba(temp_color);
          break;
        case 'p':
          sscanf(optarg, "%x", &temp_color);
          _options.path_color = rgb_to_rgba(temp_color);
          break;
        default:
          exit(0);
          break;
      }
    }

  }

  static void print_usage() {
    std::cout << "Usage: pdriver [-hd] [-xylSB <number>] [-etswvcp <hex-color>]" << std::endl;
    std::cout << " h              Prints this message" << std::endl;
    std::cout << " d              Enable diagonal paths" << std::endl;
    std::cout << " x <number>     width of canvas" << std::endl;
    std::cout << " y <number>     height of canvas" << std::endl;
    std::cout << " l <number>     cell lines width" << std::endl;
    std::cout << " S <number>     path finder sleep time" << std::endl;
    std::cout << " B <number>     back tracking sleep time" << std::endl;
    std::cout << " e <hex-color>  empty cell color" << std::endl;
    std::cout << " s <hex-color>  start cell color" << std::endl;
    std::cout << " t <hex-color>  target cell color" << std::endl;
    std::cout << " w <hex-color>  wall cell color" << std::endl;
    std::cout << " v <hex-color>  visited cell color" << std::endl;
    std::cout << " c <hex-color>  seen cell color" << std::endl;
    std::cout << " p <hex-color>  path color" << std::endl;
    exit(0);
  }

  Board *_board;
  Visualizer *_visualizer;

  int _grid_w, _grid_h;
  options_t _options;
};

int main(int argc, char *argv[]) {
  Program p(argc, argv);
  p.run();
  return 0;
}