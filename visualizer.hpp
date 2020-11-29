#pragma once

#include <SDL2/SDL.h>

class Visualizer {
public:
  static void init();
  static void quit();
  Visualizer(const char *);
  ~Visualizer();
  void run();
  bool is_running() { return _is_running; }
private:
  SDL_Window *_window;
  SDL_Renderer *_renderer;
  bool _is_running;
};