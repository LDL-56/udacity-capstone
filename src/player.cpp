#include "player.h"
#include <cmath>
#include <iostream>

void Player::Update(Player opponent) {

  change_dir = true;

  SDL_Point prev_cell{
      static_cast<int>(head_x),
      static_cast<int>(head_y)};  // We first capture the head's cell before updating.

  UpdateHead();
  SDL_Point current_cell{
      static_cast<int>(head_x),
      static_cast<int>(head_y)};  // Capture the head's cell after updating.

  // Update all of the body vector items if the player head has moved to a new
  // cell.
  if (current_cell.x != prev_cell.x || current_cell.y != prev_cell.y) {
    UpdateBody(current_cell, prev_cell, opponent);
  }
}

void Player::UpdateHead() {

  // If the player is using boost, increase the speed for boost_length number of loops
  float current_speed{speed};
  // If we're boosting
  if (boosting){
    // Decrease our boost duration (boost is in short bursts)
    if (boost_duration > 0){
      boost_duration -= 1;
    }
    // Apply the speed boost
    current_speed = speed + speed_boost;
    }

  // If this is our last update using boost, set boosting to false, and reset the boost duration to max
  if (boost_duration == 0){
    boosting = false;
    boost_duration = full_boost_duration;
  }

  // std::cout << name << " boosting: " << boosting << " boost_time: " << boost_time << std::endl;

  switch (direction) {
    case Direction::kUp:
      head_y -= current_speed;
      break;

    case Direction::kDown:
      head_y += current_speed;
      break;

    case Direction::kLeft:
      head_x -= current_speed;
      break;

    case Direction::kRight:
      head_x += current_speed;
      break;
  }

  // Wrap the Snake around to the beginning if going off of the screen.
  head_x = fmod(head_x + grid_width, grid_width);
  head_y = fmod(head_y + grid_height, grid_height);
}

void Player::UpdateBody(SDL_Point &current_head_cell, SDL_Point &prev_head_cell, Player opponent) {
  // Add previous head location to vector
  // Need to make sure there aren't any gaps in the player body caused by a speed > 1

  // std::cout << "previous: [" << prev_head_cell.x << "," << prev_head_cell.y << "]  boosting: " << boosting << std::endl;
  // std::cout << "current:  [" << current_head_cell.x << "," << current_head_cell.y << "]  boosting: " << boosting << std::endl;

  // Find distance change in both dimensions
  int x_change = current_head_cell.x - prev_head_cell.x;
  int y_change = current_head_cell.y - prev_head_cell.y;

  // Find the number of gaps between body pieces
  int x_gaps = std::abs(x_change) - 1;
  int y_gaps = std::abs(y_change) - 1;

  // Guard to allow players to pass through walls
  if (x_gaps > (speed+speed_boost)){x_gaps = 0;}
  if (y_gaps > (speed+speed_boost)){y_gaps = 0;}

  // If moving horizontal with speed more than 1, need to fill in the body gaps
  if (x_gaps > 0){
    body.push_back(prev_head_cell);
    SDL_Point filler;

    if (x_change < -1){ // If moving to the left
      for (int i = 1; i <= x_gaps; i++){
        filler.x = prev_head_cell.x - i;
        filler.y = prev_head_cell.y;
        body.push_back(filler);
      }
    }
    if (x_change > 1){ // If moving to the right
      for (int i = 1; i <= x_gaps; i++){
        filler.x = prev_head_cell.x + i;
        filler.y = prev_head_cell.y;
        body.push_back(filler);
      }
    }
  }

  // If moving vertical with speed more than 1, need to fill in the body gaps
  if (y_gaps > 0){
    body.push_back(prev_head_cell);
    SDL_Point filler;

    if (y_change < -1){ // If moving down
      for (int i = 1; i <= y_gaps; i++){
        filler.x = prev_head_cell.x;
        filler.y = prev_head_cell.y - i;
        body.push_back(filler);
      }
    }
    if (y_change > 1){ // If moving up
      for (int i = 1; i <= y_gaps; i++){
        filler.x = prev_head_cell.x;
        filler.y = prev_head_cell.y + i;
        body.push_back(filler);
      }
    }
  }

  // If we're not moving more than one speed, then add in prev_head_cell to body without any filler pieces
  if ((x_gaps == 0 || x_gaps == -1) && (y_gaps == 0 || y_gaps == -1)){body.push_back(prev_head_cell);}
  
  size++;

  // Check if the player has died.
  for (auto const &item : body) {
    if ((current_head_cell.x == item.x && current_head_cell.y == item.y)) {
      alive = false;
    }
  }

  // If a player crashes into the other player, they die
  for (auto const &item : opponent.body) {
    if ((current_head_cell.x == item.x && current_head_cell.y == item.y)) {
      alive = false;
    }
  }

}