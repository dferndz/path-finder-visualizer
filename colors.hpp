#pragma once

#include <SDL2/SDL.h>

typedef unsigned color_t;

struct Color {
  const static color_t Blue = 0x4287f5ff;
  const static color_t Green = 0x3bff55ff;
  const static color_t Red = 0xff3030ff;
  const static color_t Yellow = 0xf5f23dff;
  const static color_t White = 0xffffffff;
  const static color_t LightGreen = 0xadffbaff;
  const static color_t DarkGreen = 0x00b542ff;
};

SDL_Color u_to_color(color_t);

void set_sdl_render_color(SDL_Renderer *, color_t);