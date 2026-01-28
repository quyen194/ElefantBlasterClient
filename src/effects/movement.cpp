/********************************************************************
  Copyright 2014, Cong Quyen Knight. All rights reserved

  project:   Aries Games Project
  author:    quyen19492
  email:     quyen19492@gmail.com

  created:   2025/11/09 11:15
  filename:  ElefantBlaster/ElefantBlasterClient/effects/movement.cpp

  purpose:   Define Movement struct for handling entity movement.
*********************************************************************/


// -----------------------------------------------------------------------------
#include "effects/movement.hpp"
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------

MoveDir Movement::PosToDir(glm::vec2 pos_start, glm::vec2 pos_end) {
  if (pos_end.x == pos_start.x && pos_end.y == pos_start.y - 1) {
    return MoveDir::kUp;
  }
  if (pos_end.x == pos_start.x && pos_end.y == pos_start.y + 1) {
    return MoveDir::kDown;
  }
  if (pos_end.y == pos_start.y && pos_end.x == pos_start.x - 1) {
    return MoveDir::kLeft;
  }
  if (pos_end.y == pos_start.y && pos_end.x == pos_start.x + 1) {
    return MoveDir::kRight;
  }

  return MoveDir::kDown;
}
// -----------------------------------------------------------------------------

glm::vec2 Movement::DirToPos(glm::vec2 pos, MoveDir dir) {
  float delta = 1.0f;

  switch (dir) {
    case MoveDir::kLeft:
      return glm::vec2(pos.x - delta, pos.y);
    case MoveDir::kRight:
      return glm::vec2(pos.x + delta, pos.y);
    case MoveDir::kUp:
      return glm::vec2(pos.x, pos.y - delta);
    case MoveDir::kDown:
      return glm::vec2(pos.x, pos.y + delta);
  }

  return glm::vec2(pos.x, pos.y);
}
// -----------------------------------------------------------------------------
