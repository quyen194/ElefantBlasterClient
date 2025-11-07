/********************************************************************
  Copyright 2014, Cong Quyen Knight. All rights reserved

  project:   Aries Games Project
  author:    quyen19492
  email:     quyen19492@gmail.com

  created:   2025/11/05 16:18
  filename:  ElefantBlaster/ElefantBlasterClient/entities/spoil.h

  purpose:
*********************************************************************/


// -----------------------------------------------------------------------------
#ifndef ELEFANT_BLASTER_CLIENT_ENTITIES_SPOIL_HPP
#define ELEFANT_BLASTER_CLIENT_ENTITIES_SPOIL_HPP
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
#include <glm/glm.hpp>
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
namespace _AssetSpoilType {
enum T {
  kDragonEggMystic,
  kDragonEggAttack,
  kDragonEggDelay,
  kDragonEggSpeed,
  kMax,
};
};
typedef _AssetSpoilType::T AssetSpoilType;
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
namespace _SpoilType {
enum T {
  kDragonEggSpeed = 3,
  kDragonEggAttack = 4,
  kDragonEggDelay = 5,
  kDragonEggMystic = 6,
};
};
typedef _SpoilType::T SpoilType;
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------

struct Spoil {
  SpoilType type;
  glm::vec2 map_pos;
  glm::vec2 screen_pos;
  SDL_Texture *texture = nullptr;
  SDL_FRect rect;
};
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
#endif  // ELEFANT_BLASTER_CLIENT_ENTITIES_SPOIL_HPP
// -----------------------------------------------------------------------------
