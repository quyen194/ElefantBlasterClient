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
namespace _SpoilType {
enum T {
  kDragonEggMystic,
  kDragonEggAttack,
  kDragonEggDelay,
  kDragonEggSpeed,
  kMax,
};
};
typedef _SpoilType::T SpoilType;
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------

struct Spoil {
  SpoilType type;
  glm::vec2 map_pos;
};
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
#endif  // ELEFANT_BLASTER_CLIENT_ENTITIES_SPOIL_HPP
// -----------------------------------------------------------------------------
