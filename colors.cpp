#include <random>
#include "colors.hpp"

#define C_R_MASK 0xff000000
#define C_G_MASK 0x00ff0000
#define C_B_MASK 0x0000ff00
#define C_A_MASK 0x000000ff

Color u_to_color(unsigned c) {
  Color color;

  color.r = (c & C_R_MASK) >> 24;
  color.g = (c & C_G_MASK) >> 16;
  color.b = (c & C_B_MASK) >> 8;
  color.a = (c & C_A_MASK);

  return color;
}

void set_sdl_render_color(SDL_Renderer *r, unsigned c) {
  Color color = u_to_color(c);
  SDL_SetRenderDrawColor(r, color.r, color.g, color.b, color.a);
}