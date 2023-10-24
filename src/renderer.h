#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <SDL.h>
#include <SDL2/SDL_ttf.h>
#include "player.h"

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  void Render(Player const player);
  void ClearScreen();
  void UpdateWindowTitle(Player player1, Player player2, int fps);
  void StartScreen();
  void RenderText(SDL_Color textColor, TTF_Font* font, const char* text, float x_coord, float y_coord);

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
};

#endif