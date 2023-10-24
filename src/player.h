#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>
#include "SDL.h"

class Player {
 public:
  enum class Direction { kUp, kDown, kLeft, kRight};

  Player(Player::Direction direction, int grid_width, int grid_height, int x_offset, std::string name, std::string color)
      : direction(direction),
        head_x(grid_width / 2 + x_offset),
        head_y(grid_height / 2),
        name(name),
        color(color),
        grid_width(grid_width),
        grid_height(grid_height) {}
        

  void Update(Player opponent);

  Direction direction;

  float speed{.4f};
  int size{1};
  bool alive{true};
  float head_x;
  float head_y;
  std::string name;
  std::string color;
  bool boosting{false};
  int full_boost_duration{65}; // does not change
  int boost_duration = full_boost_duration; // changes
  int boosts_remaining{6};
  bool change_dir{true};
  float speed_boost{.9f};

  std::vector<SDL_Point> body;


 private:
  void UpdateHead();
  void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell, Player opponent);

  // bool growing{false};
  int grid_width;
  int grid_height;

};

#endif