#include "controller.h"
#include <iostream>
#include "SDL.h"
#include "player.h"

void Controller::ChangeDirection(Player &player, Player::Direction input,
                                 Player::Direction opposite) const {
  if ((player.direction != opposite || player.size == 1) && player.change_dir) player.direction = input;
  player.change_dir = false;
  return;
}

void Controller::HandleInput(bool &running, Player &player1, Player &player2) const {

  SDL_Event e;
  while (SDL_PollEvent(&e)) {

    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_KEYDOWN) {
      
      // Handle player 1 controls
      switch (e.key.keysym.sym) {
        case SDLK_UP:
          ChangeDirection(player1, Player::Direction::kUp, Player::Direction::kDown);
          break;
        case SDLK_DOWN:
          ChangeDirection(player1, Player::Direction::kDown, Player::Direction::kUp);
          break;
        case SDLK_LEFT:
          ChangeDirection(player1, Player::Direction::kLeft, Player::Direction::kRight);
          break;
        case SDLK_RIGHT:
          ChangeDirection(player1, Player::Direction::kRight, Player::Direction::kLeft);
          break;
        case SDLK_RSHIFT:
          if (player1.boosts_remaining > 0 && !player1.boosting){
              player1.boosting = true;
              player1.boosts_remaining -= 1;
              break;
              }

        // Handle player 2 controls
        case SDLK_w:
          ChangeDirection(player2, Player::Direction::kUp, Player::Direction::kDown);
          break;
        case SDLK_s:
          ChangeDirection(player2, Player::Direction::kDown, Player::Direction::kUp);
          break;
        case SDLK_a:
          ChangeDirection(player2, Player::Direction::kLeft, Player::Direction::kRight);
          break;
        case SDLK_d:
          ChangeDirection(player2, Player::Direction::kRight, Player::Direction::kLeft);
          break;
        case SDLK_LSHIFT:
          if (player2.boosts_remaining > 0 && !player2.boosting){
            player2.boosting = true;
            player2.boosts_remaining -= 1;
            break;
          }
      }
    }
  }
}