#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"

int WinMain() {
  constexpr std::size_t kFramesPerSecond{120};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{1200};
  constexpr std::size_t kScreenHeight{800};
  constexpr std::size_t kGridWidth{600};
  constexpr std::size_t kGridHeight{400};

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Game game(kGridWidth, kGridHeight);

  bool startGame = false;
  bool quitGame = false;

  // Render the start screen
  renderer.StartScreen();

  // Launch the Start Screen
  SDL_Event e;
  while (!startGame && !quitGame) {
  
      // Check for game start or quit
      while (SDL_PollEvent(&e) != 0) {
          if (e.type == SDL_QUIT) {
              quitGame = true;
          }
          else if (e.type == SDL_KEYDOWN) {
              if (e.key.keysym.sym == SDLK_g){
              startGame = true; 
            }
          }
      }
  }

  if (!quitGame){
    game.Run(controller, renderer, kMsPerFrame);
    std::cout << "Game has terminated successfully!\n";
    if (game.GetWinner().name != ""){
      std::cout << "Winner!! " << game.GetWinner().name << "\n";
      std::cout << game.GetWinner().name << " Size: " << game.GetWinner().size << "\n";
    }
  }
  else{
    std::cout << "Game has terminated successfully!\n";
  }

  return 0;
}