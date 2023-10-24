#include "renderer.h"
#include <iostream>
#include <string>

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height) {

  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Initialize SDL_ttf for start screen
  if (TTF_Init() == -1) {
    std::cerr << "TTF_Init failed: " << TTF_GetError() << std::endl;
}

  // Create Window
  sdl_window = SDL_CreateWindow("Tron Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  TTF_Quit();
  SDL_Quit();

}

void Renderer::StartScreen(){

  std::cout << "\n";

  ClearScreen();


  // %%%%%% BEGIN TITLE TEXT %%%%%%%%%%
  // Set text color for title
  SDL_Color textColor = {255, 255, 255};  // White color

  // Load font for title
  TTF_Font* font = TTF_OpenFont("../resources/arial.ttf", 36);

  if (font == nullptr) {
    std::cerr << "Font loading failed: " << TTF_GetError() << "\n";
    return;
  }

  // Set additional parameters for title
  const char* text = "Tron Game";
  float x_coord = 0.5;
  float y_coord = 0.1;
  
  // Render Title Text
  RenderText(textColor, font, text, x_coord, y_coord);
  // %%%%%%% END TITLE TEXT %%%%%%%%%%%

  // %%%%%%%% BEGIN BUILD INSTRUCTIONS TEXT %%%%%%%%%%
  textColor = {255, 255, 255};
  font = TTF_OpenFont("../resources/arial.ttf", 24);
  if (font == nullptr) {
    std::cerr << "Font loading failed: " << TTF_GetError() << "\n";
    return;
  }
  text = "Instructions:";
  x_coord = 0.06;
  y_coord = 0.25;

  RenderText(textColor, font, text, x_coord, y_coord);
  // %%%%%%% END BUILD INSTRUCTIONS TEXT %%%%%%%%%%%

  // %%%%%%%% BEGIN Player1 INSTRUCTIONS TEXT %%%%%%%%%%
  textColor = {3, 255, 232}; 
  font = TTF_OpenFont("../resources/arial.ttf", 24);
  if (font == nullptr) {
    std::cerr << "Font loading failed: " << TTF_GetError() << "\n";
    return;
  }
  text = "Player1:  Use Arrow Keys to change directions, and right shift to boost";
  x_coord = 0.184;
  y_coord = 0.34;

  RenderText(textColor, font, text, x_coord, y_coord);
  // %%%%%%% END Player1 INSTRUCTIONS TEXT %%%%%%%%%%%

  // %%%%%%%% BEGIN Player2 INSTRUCTIONS TEXT %%%%%%%%%%
  textColor = {245, 122, 7};
  font = TTF_OpenFont("../resources/arial.ttf", 24);
  if (font == nullptr) {
    std::cerr << "Font loading failed: " << TTF_GetError() << "\n";
    return;
  }
  text = "Player2:  Use W, A, S, D Keys to change directions, and left shift to boost";
  x_coord = 0.2;
  y_coord = 0.40;

  RenderText(textColor, font, text, x_coord, y_coord);
  // %%%%%%% END Player1 INSTRUCTIONS TEXT %%%%%%%%%%%


  // %%%%%%%% BEGIN StartGame INSTRUCTIONS TEXT %%%%%%%%%%
  textColor = {150, 225, 150}; 
  font = TTF_OpenFont("../resources/arial.ttf", 24);
  if (font == nullptr) {
    std::cerr << "Font loading failed: " << TTF_GetError() << "\n";
    return;
  }
  text = "When you're ready to begin, press the 'G' key on the keyboard";
  x_coord = 0.5;
  y_coord = 0.85;
  RenderText(textColor, font, text, x_coord, y_coord);
}

void Renderer::ClearScreen(){

  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

}

void Renderer::Render(Player const player) {
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Render player's light bike
  if (player.color == "orange"){SDL_SetRenderDrawColor(sdl_renderer, 245, 122, 7, 255);}
  if (player.color == "blue"){SDL_SetRenderDrawColor(sdl_renderer, 3, 255, 232, 255);}
  
  for (SDL_Point const &point : player.body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Render player's head
  block.x = static_cast<int>(player.head_x) * block.w;
  block.y = static_cast<int>(player.head_y) * block.h;
  if (player.alive) {
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
  } else {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
  }
  SDL_RenderFillRect(sdl_renderer, &block);

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(Player player1, Player player2, int fps) {
  // std::string title{"player Score: " + std::to_string(score) + " FPS: \t \t \t" + std::to_string(fps)};
  std::string title{"Orange Boosts Remaining: " + std::to_string(player2.boosts_remaining) + 
                    "\tBlue Boosts Remaining: " +  std::to_string(player1.boosts_remaining) + 
                    " \t \t FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}


void Renderer::RenderText(SDL_Color textColor, 
                          TTF_Font* font, 
                          const char* text, 
                          float x_coord, 
                          float y_coord){


  if (font == nullptr) {
    std::cerr << "Font loading failed: " << TTF_GetError() << "\n";
    return;
  }

  // Render the text
  SDL_Surface* textSurface = TTF_RenderText_Solid(font, text, textColor);

  if (textSurface == nullptr) {
    std::cerr << "Text rendering failed: " << TTF_GetError() << "\n";
    return;
  }

  // Create a texture from the surface
  SDL_Texture* textTexture = SDL_CreateTextureFromSurface(sdl_renderer, textSurface);
  if (textTexture == nullptr) {
    std::cerr << "Texture creation failed: " << SDL_GetError() << "\n";
    return;
  }

  // Set title text location
  int textWidth = textSurface->w;
  int textHeight = textSurface->h;
  int x = (screen_width - textWidth) * x_coord;
  int y = (screen_height - textHeight) * y_coord;

  // Create a destination rectangle for the text
  SDL_Rect destRect = {x, y, textWidth, textHeight};

  // Render the text texture
  SDL_RenderCopy(sdl_renderer, textTexture, nullptr, &destRect);

  // Update the screen
  SDL_RenderPresent(sdl_renderer);

  // Clean up the font, surface, and texture
  TTF_CloseFont(font);
  SDL_FreeSurface(textSurface);
  SDL_DestroyTexture(textTexture);

}