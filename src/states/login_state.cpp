/********************************************************************
  Copyright 2026, Cong Quyen Knight. All rights reserved

  project:   Aries Games: Elefant Blaster
  author:    quyen19492
  email:     quyen19492@gmail.com

  created:   2026/01/29 05:09
  filename:  ElefantBlaster/ElefantBlasterClient/states/login_state.cpp

  purpose:   Define LoginState class for managing the login state.
*********************************************************************/


// -----------------------------------------------------------------------------
#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_sdlrenderer3.h>

#include "states/login_state.hpp"
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------

LoginState::LoginState(SDLState& sdl_state,
                       AssetManager& asset_manager,
                       ImguiState& imgui_state)
    : sdl_state_(sdl_state),
      asset_manager_(asset_manager),
      imgui_state_(imgui_state),
      username_{0} {}
// -----------------------------------------------------------------------------

LoginState::~LoginState() {
  Cleanup();
}
// -----------------------------------------------------------------------------

bool LoginState::Initialize() {
  return true;
}
// -----------------------------------------------------------------------------

void LoginState::Cleanup() {
}
// -----------------------------------------------------------------------------

void LoginState::OnDraw() {
  const ImGuiViewport* vp = ImGui::GetMainViewport();

  ImGui::SetNextWindowPos(vp->GetCenter(), ImGuiCond_Always, ImVec2(0.5f, 0.5f));

  float ui_scale = imgui_state_.UiScale();

  ImGui::PushFont(asset_manager_.ImFontRegular(), 24 * ui_scale);

  ImGui::Begin("Login",
               nullptr,
               ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
                   ImGuiWindowFlags_NoMove | ImGuiWindowFlags_AlwaysAutoResize);

  ImGui::Text("Welcome to Elefant Blaster!");
  ImGui::InputText("##username", username_, IM_ARRAYSIZE(username_));
  if (ImGui::Button("Login", ImVec2(200 * ui_scale, 50 * ui_scale))) {
    //
  }
  ImGui::End();

  ImGui::PopFont();

}
// -----------------------------------------------------------------------------

void LoginState::OnEvent(SDL_Event &event) {
}
// -----------------------------------------------------------------------------
