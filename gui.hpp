#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "colors.hpp"

#define DEFAULT_B_W 80
#define DEFAULT_B_H 40

#define DEFAULT_B_COLOR Color::Blue


class Button {
public:
  Button(SDL_Renderer* r, TTF_Font* f, const char * text, int x, int y, unsigned c = DEFAULT_B_COLOR, int w = DEFAULT_B_W, int h = DEFAULT_B_H);
  ~Button();
  bool is_pressed();
  unsigned get_color() { return _color; }
  SDL_Rect* get_rect() { return &_rect; }
  void draw_button(SDL_Renderer*, bool solid = false);
private:
  SDL_Rect _rect;
  SDL_Rect _text_area;
  SDL_Texture *_texture;
  SDL_Texture *_solid_texture;

  char *_text;
  unsigned _color; 
};