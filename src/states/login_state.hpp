/********************************************************************
  Copyright 2026, Cong Quyen Knight. All rights reserved

  project:   Aries Games: Elefant Blaster
  author:    quyen19492
  email:     quyen19492@gmail.com

  created:   2026/01/29 05:04
  filename:  ElefantBlaster/ElefantBlasterClient/states/login_state.hpp

  purpose:   Define LoginState class for managing the login state.
*********************************************************************/


// -----------------------------------------------------------------------------
#ifndef ELEFANT_BLASTER_CLIENT_STATES_LOGIN_STATE_HPP
#define ELEFANT_BLASTER_CLIENT_STATES_LOGIN_STATE_HPP
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
#include "definitions/macro.hpp"

#include "core/asset_manager.hpp"
#include "core/imgui_state.hpp"
#include "core/sdl_state.hpp"
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------

class LoginState {
 public:
  LoginState(SDLState& sdl_state,
             AssetManager& asset_manager,
             ImguiState& imgui_state);
  virtual ~LoginState();

  bool Initialize();

  void OnDraw();
  void OnEvent(SDL_Event &event);

 private:
  void Cleanup();

  void OnSubmit();

 private:
  SDLState &sdl_state_;
  AssetManager &asset_manager_;
  ImguiState& imgui_state_;

  char username_[64];
  char password_[64];
  bool remember_;

 private:
  DISALLOW_COPY_AND_ASSIGN(LoginState);
};
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
#endif  // ELEFANT_BLASTER_CLIENT_STATES_LOGIN_STATE_HPP
// -----------------------------------------------------------------------------
