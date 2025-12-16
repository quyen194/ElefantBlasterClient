/********************************************************************
  Copyright 2014, Cong Quyen Knight. All rights reserved

  project:   Aries Games Project
  author:    quyen19492
  email:     quyen19492@gmail.com

  created:   2025/11/08 16:24
  filename:  ElefantBlaster/ElefantBlasterClient/effects/movement.hpp

  purpose:
*********************************************************************/


// -----------------------------------------------------------------------------
#ifndef ELEFANT_BLASTER_CLIENT_EFFECTS_MOVEMENT_HPP
#define ELEFANT_BLASTER_CLIENT_EFFECTS_MOVEMENT_HPP
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
#include "glm/glm.hpp"

#include <SDL3/SDL.h>

#include "effects/animation.hpp"
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
namespace _MoveDir {
enum T {
  kStand = 0,
  kLeft = 1,
  kRight = 2,
  kUp = 3,
  kDown = 4,
  kDropBomb = 'b',
  kStop = 'x',
};
}
typedef _MoveDir::T MoveDir;
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------

struct Movement {
  static MoveDir PosToDir(glm::vec2 pos_start, glm::vec2 pos_end);
  static glm::vec2 DirToPos(glm::vec2 pos, MoveDir dir);

  glm::vec2 map_pos_start;
  glm::vec2 map_pos_end;
  glm::vec2 screen_pos_start;
  glm::vec2 screen_pos_end;
  glm::vec2 screen_pos_current;
  MoveDir dir;
  float speed;  // pixel per second
  Animation animation;
  SDL_FRect rect;
};
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
#endif  // ELEFANT_BLASTER_CLIENT_EFFECTS_MOVEMENT_HPP
// -----------------------------------------------------------------------------
