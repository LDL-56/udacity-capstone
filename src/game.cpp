#include "game.h"
#include <iostream>
#include <thread>
#include <algorithm>
#include <iterator>
#include "SDL.h"


Game::Game(std::size_t grid_width, std::size_t grid_height)
    : player1(Player::Direction::kLeft, grid_width, grid_height, 300, "Player1", "blue"),
      player2(Player::Direction::kRight, grid_width, grid_height, -300, "Player2", "orange"),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)),
      winner(Player::Direction::kUp, grid_width, grid_height, 0, "", "") {}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  renderer.ClearScreen();

  while (running) {
    frame_start = SDL_GetTicks();

    controller.HandleInput(running, player1, player2);

    Update();

    renderer.Render(player1);
    renderer.Render(player2);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(player1, player2, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}


void Game::Update() {

  // If one of the players dies, don't perform updates
  if (!player1.alive){
    SetWinner(player2);
    return;
  }

  if (!player2.alive){
    SetWinner(player1);
    return;
  }

  player1.Update(player2);
  player2.Update(player1);
}


void Game::SetWinner(Player player) { winner = player; }
Player Game::GetWinner() const { return winner; }