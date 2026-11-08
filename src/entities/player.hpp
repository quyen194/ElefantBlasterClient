/********************************************************************
  Copyright 2014, Cong Quyen Knight. All rights reserved

  project:   Aries Games Project
  author:    quyen19492
  email:     quyen19492@gmail.com

  created:   2025/11/08 6:09
  filename:  ElefantBlaster/ElefantBlasterClient/entities/player.hpp

  purpose:   Define Player structure for player entities.
*********************************************************************/


// -----------------------------------------------------------------------------
#ifndef ELEFANT_BLASTER_CLIENT_ENTITIES_PLAYER_HPP
#define ELEFANT_BLASTER_CLIENT_ENTITIES_PLAYER_HPP
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
#include <map>
#include <string>

#include <aries_base/utils/get_default.hpp>

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
  k3,
  k4,
  k5,
  k6,
  k7,
  k8,
  kMax,
};
}
typedef _PlayerNo::T PlayerNo;
// -----------------------------------------------------------------------------
inline const std::string GetId(const PlayerNo e) {
  static const std::map<PlayerNo, std::string> kMap = {
      {PlayerNo::k1,  "PlayerNo_01"},
      {PlayerNo::k2,  "PlayerNo_02"},
      {PlayerNo::k3,  "PlayerNo_03"},
      {PlayerNo::k4,  "PlayerNo_04"},
      {PlayerNo::k5,  "PlayerNo_05"},
      {PlayerNo::k6,  "PlayerNo_06"},
      {PlayerNo::k7,  "PlayerNo_07"},
      {PlayerNo::k8,  "PlayerNo_08"},
  };

  return aries_base::utils::GetDefault(kMap, e, std::string("Unknown"));
}
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
