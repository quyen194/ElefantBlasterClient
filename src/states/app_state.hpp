/********************************************************************
  Copyright 2014, Cong Quyen Knight. All rights reserved

  project:   Aries Games Project
  author:    quyen19492
  email:     quyen19492@gmail.com

  created:   2025/11/06 6:09
  filename:  ElefantBlaster/ElefantBlasterClient/states/game_state.hpp

  purpose:   Define GameState class for managing the main game state.
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

class GameState : public MapManager {
 public:
  GameState();
  virtual ~GameState();

  static GameState* CreateInstance();

  SDL_AppResult AppQuit() { return app_quit_; }

  bool Initialize();

  void OnLoop();
  void Update(float delta_time);
  void Draw();

  void OnEvent(SDL_Event &event);
  void HandleKeyInput(Player *player, SDL_Event &event);

  void TestParsePlayers();

 private:
  SDLState sdl_state_;
  AssetManager asset_manager_;

 private:
  SDL_AppResult app_quit_;

  uint64_t app_time_;

  static GameState *instance_;

 private:
  DISALLOW_COPY_AND_ASSIGN(GameState);
};
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
#endif  // ELEFANT_BLASTER_CLIENT_STATES_GAME_STATE_HPP
// -----------------------------------------------------------------------------
