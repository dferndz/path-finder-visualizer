#include <random>
#include <string.h>

#include "visualizer.hpp"
#include "colors.hpp"

#define DEFAULT_W 800
#define DEFAULT_H 600

int randInt(int rmin, int rmax) {
    return rand() % rmax + rmin;
}

Visualizer::Visualizer(const char* title) {
  _window = SDL_CreateWindow(
    title, 
    SDL_WINDOWPOS_CENTERED, 
    SDL_WINDOWPOS_CENTERED,
    DEFAULT_W,
    DEFAULT_H,
    SDL_WINDOW_OPENGL
  );

  _renderer = SDL_CreateRenderer(
    _window,
    -1,
    SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
  );

  _is_running = false;

  set_sdl_render_color(_renderer, Color::Blue);
}

Visualizer::~Visualizer() {
  SDL_DestroyRenderer(_renderer);
  SDL_DestroyWindow(_window);
}

void Visualizer::run() {
  _is_running = true;
    SDL_Event event;
    while(_is_running) {
        // Process events
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                _is_running = false;
            } else if(event.type == SDL_KEYDOWN) {
                const char *key = SDL_GetKeyName(event.key.keysym.sym);
                if(strcmp(key, "C") == 0) {
                    set_sdl_render_color(_renderer, rand());
                }                    
            }
        }

        // Clear screen
        SDL_RenderClear(_renderer);

        // Draw

        // Show what was drawn
        SDL_RenderPresent(_renderer);
    }
}

void Visualizer::init() {
  SDL_Init(SDL_INIT_VIDEO);
}

void Visualizer::quit() {
  SDL_Quit();
}