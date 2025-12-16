/********************************************************************
  Copyright 2014, Cong Quyen Knight. All rights reserved

  project:   Aries Games Project
  author:    quyen19492
  email:     quyen19492@gmail.com

  created:   2025/11/06 6:09
  filename:  ElefantBlaster/ElefantBlasterClient/states/game_state.hpp

  purpose:
*********************************************************************/


// -----------------------------------------------------------------------------
#ifndef ELEFANT_BLASTER_CLIENT_STATES_GAME_STATE_HPP
#define ELEFANT_BLASTER_CLIENT_STATES_GAME_STATE_HPP
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
#include "definitions/macro.hpp"

#include "states/sdl_state.hpp"
#include "core/asset_manager.hpp"
#include "map/map_manager.hpp"
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------

class GameState {
 public:
  GameState();
  virtual ~GameState();

  void Loop();

 private:
  SDLState sdl_state_;
  AssetManager asset_manager_;
  MapManager map_manager_;

 private:
  bool inited_;

 private:
  DISALLOW_COPY_AND_ASSIGN(GameState);
};
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
#endif  // ELEFANT_BLASTER_CLIENT_STATES_GAME_STATE_HPP
// -----------------------------------------------------------------------------
