/********************************************************************
  Copyright 2026, Cong Quyen Knight. All rights reserved

  project:   Aries Games: Elefant Blaster
  author:    quyen19492
  email:     quyen19492@gmail.com

  created:   2026/10/10 15:03
  filename:  ElefantBlaster/ElefantBlasterClient/core/imgui_state.hpp

  purpose:   Define ImguiState class for managing Imgui initialization and state.
*********************************************************************/


// -----------------------------------------------------------------------------
#ifndef ELEFANTBLASTERCLIENT_CORE_IMGUI_STATE_HPP
#define ELEFANTBLASTERCLIENT_CORE_IMGUI_STATE_HPP
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
#include <imgui.h>

#include "definitions/macro.hpp"

#include "core/sdl_state.hpp"
#include "core/asset_manager.hpp"
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------

class ImguiState {
 public:
  ImguiState(SDLState &sdl_state, AssetManager &asset_manager);
  virtual ~ImguiState();

  static ImguiState& Instance() { return *instance_; }
  float UiScale() { return ui_scale_; }

  bool Initialize();
  void Cleanup();

  void BeginFrame();
  void EndFrame();

  bool OnEvent(SDL_Event &event);

  bool WantMouse();
  bool WantKeyboard();

 private:
  bool inited_;

  SDLState &sdl_state_;
  AssetManager &asset_manager_;

  float ui_scale_;
  ImGuiStyle base_style_;

 private:
  static ImguiState* instance_;

 private:
  DISALLOW_COPY_AND_ASSIGN(ImguiState);
};
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
#endif  // ELEFANTBLASTERCLIENT_CORE_IMGUI_STATE_HPP
// -----------------------------------------------------------------------------
