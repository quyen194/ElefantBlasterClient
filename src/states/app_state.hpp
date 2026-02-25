/********************************************************************
  Copyright 2014, Cong Quyen Knight. All rights reserved

  project:   Aries Games Project
  author:    quyen19492
  email:     quyen19492@gmail.com

  created:   2025/11/06 6:09
  filename:  ElefantBlaster/ElefantBlasterClient/states/app_state.hpp

  purpose:   Define AppState class for managing the application state.
*********************************************************************/


// -----------------------------------------------------------------------------
#ifndef ELEFANT_BLASTER_CLIENT_STATES_APP_STATE_HPP
#define ELEFANT_BLASTER_CLIENT_STATES_APP_STATE_HPP
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
#include "definitions/macro.hpp"

#include "states/sdl_state.hpp"
#include "core/asset_manager.hpp"
#include "states/match_state.hpp"
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------

class AppState {
 public:
  AppState();
  virtual ~AppState();

  static AppState* CreateInstance();

  SDL_AppResult AppQuit() { return app_quit_; }

  bool Initialize();

  void OnLoop();
  void OnUpdate(float delta_time);
  void OnDraw();

  void OnEvent(SDL_Event &event);
  void OnHandleKeyInput(SDL_KeyboardEvent &event);

 private:
  SDLState sdl_state_;
  AssetManager asset_manager_;
  MatchState match_state_;

 private:
  SDL_AppResult app_quit_;

  uint64_t app_time_;

  static AppState *instance_;

 private:
  DISALLOW_COPY_AND_ASSIGN(AppState);
};
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
#endif  // ELEFANT_BLASTER_CLIENT_STATES_APP_STATE_HPP
// -----------------------------------------------------------------------------
