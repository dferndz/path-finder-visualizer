#include "button.hpp"
#include <string.h>

#define BUTTON_PADDING 10

Button::Button(SDL_Renderer* r, TTF_Font* f, const char* text, int x, int y, unsigned c, int w, int h) {
  _rect.x = x;
  _rect.y = y;
  _rect.w = w;
  _rect.h = h;
  _color = c;

  _text_area.x = x + BUTTON_PADDING;
  _text_area.y = y + BUTTON_PADDING;
  _text_area.w = w - 2*BUTTON_PADDING;
  _text_area.h = h - 2*BUTTON_PADDING;

  _texture = SDL_CreateTextureFromSurface(r, TTF_RenderText_Solid(f, text, u_to_color(c)));
  _solid_texture = SDL_CreateTextureFromSurface(r, TTF_RenderText_Solid(f, text, u_to_color(Color::White)));

  _text = new char[strlen(text)];
  strcpy(_text, text);
}

Button::~Button() {
  delete [] _text;
}

bool Button::is_pressed() {
  int x, y;
  int mouse_status = SDL_GetMouseState(&x, &y);

  return ((mouse_status & SDL_BUTTON(1)) &&
    x >= _rect.x && x <= _rect.x + _rect.w &&
    y >= _rect.y && y <= _rect.y + _rect.h
  );
}

void Button::draw_button(SDL_Renderer* renderer, bool solid) {
  set_sdl_render_color(renderer, _color);

  if(solid) {
    SDL_RenderFillRect(renderer, &_rect);
    SDL_RenderCopy(renderer, _solid_texture, NULL, &_text_area);
  } else {
    SDL_RenderDrawRect(renderer, &_rect);
    SDL_RenderCopy(renderer, _texture, NULL, &_text_area);
  }
  
}