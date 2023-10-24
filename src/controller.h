#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "player.h"

class Controller {
 public:
  void HandleInput(bool &running, Player &player1, Player &player2) const;

 private:
  void ChangeDirection(Player &player1, Player::Direction input,
                       Player::Direction opposite) const;
};

#endif