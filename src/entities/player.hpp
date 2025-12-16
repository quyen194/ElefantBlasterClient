/********************************************************************
  Copyright 2014, Cong Quyen Knight. All rights reserved

  project:   Aries Games Project
  author:    quyen19492
  email:     quyen19492@gmail.com

  created:   2025/11/08 6:09
  filename:  ElefantBlaster/ElefantBlasterClient/entities/player.hpp

  purpose:
*********************************************************************/


// -----------------------------------------------------------------------------
#ifndef ELEFANT_BLASTER_CLIENT_ENTITIES_PLAYER_HPP
#define ELEFANT_BLASTER_CLIENT_ENTITIES_PLAYER_HPP
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
#include <string>

#include "effects/movement.hpp"
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
namespace _AssetPlayerDir {
enum T {
  kDown,
  kUp,
  kLeft,
  kRight,
  kMax,
};
}
typedef _AssetPlayerDir::T AssetPlayerDir;
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
namespace _PlayerNo {
enum T {
  k1,
  k2,
  kMax,
};
}
typedef _PlayerNo::T PlayerNo;
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------

struct Player {
  std::string server_id;
  PlayerNo player_no;

  glm::vec2 map_pos;
  glm::vec2 screen_pos;
  SDL_Texture *texture = nullptr;
  SDL_FRect rect;
  bool is_moving = false;
  Movement movement;

  int speed;
  int power;
  int delay;
  int lives;
  int score;
  int box;
  int dragonEggSpeed;
  int dragonEggAttack;
  int dragonEggDelay;
  int dragonEggMystic;
  int dragonEggMysticAddEgg;
  int dragonEggMysticMinusEgg;
  int dragonEggMysticIsolateGate;
  int gstEggBeingAttacked;
  int quarantine;
};
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
#endif  // ELEFANT_BLASTER_CLIENT_ENTITIES_PLAYER_HPP
// -----------------------------------------------------------------------------
