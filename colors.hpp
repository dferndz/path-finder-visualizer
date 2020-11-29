#pragma once

#include <SDL2/SDL.h>

typedef const unsigned color_t;

struct Color {
  Uint8 r, g, b, a;

  static color_t Blue = 0x4287f5ff;
  static color_t Green = 0x3bff55ff;
  static color_t Red = 0xff3030ff;
  static color_t Yellow = 0xf5f23dff;
  static color_t White = 0xffffffff;
};

Color u_to_color(unsigned);

void set_sdl_render_color(SDL_Renderer *, unsigned);