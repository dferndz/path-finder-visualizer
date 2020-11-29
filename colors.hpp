#pragma once

#include <SDL2/SDL.h>

struct Color {
  Uint8 r, g, b, a;

  const static unsigned Blue = 0x4287f5ff;
};

Color u_to_color(unsigned);
void set_sdl_render_color(SDL_Renderer *, unsigned);